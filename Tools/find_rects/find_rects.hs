module Main where

import Codec.BMP
import qualified Data.ByteString as B
import Data.List
import Data.Maybe
import Data.Word
import System.Environment
import System.IO


data Interval = Interval { intervalStart :: Int
						 , intervalEnd :: Int
						 } deriving (Show)
						 
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

processLine :: [Word8] -> [Word8]
processLine = map head . group

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
			   print (width, height)
			   print $ map processLine $ reshape width $ makeBinary [255,0,255] rgba
