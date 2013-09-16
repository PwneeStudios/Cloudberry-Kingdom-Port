# Copy SFO
echo Renaming PARAM_SCEE.SFO to PARAM.SFO
cp -f Cloudberry\ PS3/PARAM_SCEE.SFO "PS3_GAME/PARAM.SFO"

# Copy SaveMeta icon
echo Copying save icon
cp -f ICON0.PNG PS3_GAME/USRDIR/ContentPS3/SaveMeta/

# Copy LocalizationCpp, since this gets updated frequently
echo Copying localizaion
cp -f ContentPS3/Localization/LocalizationCpp.tsv PS3_GAME/USRDIR/ContentPS3/Localization/

# Copy symbols before stripping
echo Saving .self with symbols
cp -f Cloudberry\ PS3/PS3_Release/Cloudberry_Kingdom.self PS3_Final_Package/Europe/

# Strip symbols
echo Stripping symbols
ppu-lv2-strip Cloudberry\ PS3/PS3_Release/Cloudberry_Kingdom.self

# Make EBOOT.BIN
echo Making EBOOT.BIN
make_fself_npdrm Cloudberry\ PS3/PS3_Release/Cloudberry_Kingdom.self "Cloudberry PS3/PS3_Release/EBOOT.BIN"

# Copy EBOOT.BIN
echo Copying EBOOT.BIN
cp -f Cloudberry\ PS3/PS3_Release/EBOOT.BIN PS3_GAME/USRDIR/

# Make the package
echo Making package
make_package_npdrm Cloudberry\ PS3/pkg_config_SCEE.txt PS3_GAME

# Copy package to PS3_Final_Package
echo Copying package
cp -f EP0001-NPEB01312_00-CLOUDBERRYKIFULL.pkg PS3_Final_Package/Europe/
