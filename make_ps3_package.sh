#!/bin/bash

pushd "Cloudberry PS3/PS3_Release"
make_fself_npdrm.exe Cloudberry_Kingdom.self EBOOT.BIN
mv EBOOT.BIN ../../PS3_GAME/USRDIR/EBOOT.BIN
popd
make_package_npdrm.exe "Cloudberry PS3/pkg_config_scea.txt" PS3_GAME
