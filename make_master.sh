# Save old master.
mv -f MASTER/Cloudberry_Kingdom.wumad MASTER/Cloudberry_Kingdom.wumad.last

# Restore to our meta directory.
rm Meta/*
cp -f CKMeta/* Meta

# Create a master.
makecfmaster.sh -r Cloudberry_Kingdom.rpx -o MASTER/Cloudberry_Kingdom -w INTERMEDIATE

# Create installable package.
#makecfdownloadimage.sh -i MASTER/Cloudberry_Kingdom.wumad

# Upload master to the WiiU.
#uploadimg.sh 1 MASTER/Cloudberry_Kingdom.wumad

