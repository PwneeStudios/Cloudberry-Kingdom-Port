#!/bin/bash

# Convert all image files to TGA.
echo Converting to TGA
for file in $(find ./Art -iname \*.png -o -iname \*.jpg)
do
	tga_file=$(echo $file | sed "s/\.[pP][nN][gG]/\.tga/" | sed "s/\.[jJ][pP][gG]/\.tga/")
	if [ ! -f $tga_file ]
	then
		echo Converting \"$file\" to \"$tga_file\"
		convert $file $tga_file
	else
		echo $tga_file exists
	fi
done

# Convert all TGA to GTX
echo Converting to GTX
for file in $(find ./Art -iname \*.tga)
do
	gtx_file=$(echo $file | sed "s/\.tga/\.gtx/")
	if [ ! -f $gtx_file ]
	then
		echo Converting \"$file\" to \"$gtx_file\"
		TexConv2.exe -i $file -o $gtx_file
	else
		echo $gtx_file exists
	fi
done

# Remove all TGA.
echo Cleaning up TGA
find ./Art -iname \*.tga | xargs -I {} rm {}

# Generate list of files.
find ./Art -iname \*.png | sed s:\./:paths.push_back\(\ \": | sed s/\.[pP][nN][gG]/\.png\"\ \)\;/ > reduced_set.txt
