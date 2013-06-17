for filename in *.vs
do
	echo $filename;
	w_o_ext=`basename $filename .vs`;
	echo "${w_o_ext}_v.cg";
	mv $filename "${w_o_ext}_v.cg";
done