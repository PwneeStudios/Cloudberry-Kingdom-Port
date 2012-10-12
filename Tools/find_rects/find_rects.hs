module Main where

import Codec.BMP
import qualified Data.ByteString as B
import Data.List
import Data.Maybe
import Data.Word
import System.Environment
import System.IO
						 
data Rect = Rect { rectX :: Int
				 , rectY :: Int
				 , rectW :: Int
				 , rectH :: Int
				 } deriving (Show)

makeBinary :: [Word8] -> B.ByteString -> [Word8]
makeBinary color rgba =
	if B.null rgba
	then []
	else let [r,g,b,a] = B.unpack $ B.take 4 rgba
		 in (if color == [r,g,b]
			then 1
			else 0) : (makeBinary color $ B.drop 4 rgba)
			
reshape :: Int -> [a] -> [[a]]
reshape _ [] = []
reshape w arr = take w arr : (reshape w $ drop w arr)

everyOther :: [a] -> [a]
everyOther [] = []
everyOther (x:xs) = x : (everyOther $ drop 1 xs)

processLine :: [Word8] -> [Int]
processLine line =
	let groups = group line;
		widths = map length groups;
		positions = scanl1 (+) $ widths
	in positions

rectify :: ([Int],[Int]) -> [Rect]
rectify ([], _) = []
rectify ([x], _) = []
rectify (_, []) = []
rectify (_, [x]) = []
rectify ([y0,y1], x0:x1:xs) = Rect x0 y0 (x1 - x0) (y1 - y0) : rectify ([y0,y1], xs)

main :: IO ()
main = do
	[fileName] <- getArgs
	handle <- openFile fileName ReadMode
	bmp <- hGetBMP handle
	case bmp of
		Left err -> print err
		Right bmp ->
			do let rgba = unpackBMPToRGBA32 bmp
			   let (width, height) = bmpDimensions bmp
			   let columns = map processLine $ reverse $ reshape width $ makeBinary [255,0,255] rgba
			   let rows = reshape 2 $ scanl1 (+) $ map length $ group columns
			   print (width, height)
			   let rects = concat $ map rectify $ zip rows $ filter ((/=) [width]) columns
			   mapM_ (\x -> putStrLn ((show $ rectX x) ++ ", "
								   ++ (show $ rectY x) ++ ", "
								   ++ (show $ rectW x) ++ ", "
								   ++ (show $ rectH x))) rects
