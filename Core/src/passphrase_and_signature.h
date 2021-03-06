/* SCE CONFIDENTIAL
* Copyright (C) 2013 Sony Computer Entertainment Inc.
* All Rights Reserved.
*/


#ifndef __SCE_NP_CONF_H__
#define __SCE_NP_CONF_H__

#include <np.h>

static const SceNpCommunicationId s_npCommunicationId = {
    {'N', 'P', 'W', 'R', '0', '4', '4', '1', '3'},
    '\0',
    0,
    0
};

/***
SceNpCommunicationPassphrase

416ea7dc6715f7fb874be27c584df3efc5757062bc2b3992c74b7d42ee450914995edf73efa5e5e7f6bc4b1687be6a0cf40fab915d7657bd0afe59b8decf07cc7ec6b7d6be22489a874eb7efda3b65d46577a7ce2a423176f8ad38a0ead670ded8c70edb8d4543c0b30e295a769efad5b76e4d00e40e2d93dbca69688ea1f097
***/

static const SceNpCommunicationPassphrase s_npCommunicationPassphrase = {
    {
        0x41,0x6e,0xa7,0xdc,0x67,0x15,0xf7,0xfb,
        0x87,0x4b,0xe2,0x7c,0x58,0x4d,0xf3,0xef,
        0xc5,0x75,0x70,0x62,0xbc,0x2b,0x39,0x92,
        0xc7,0x4b,0x7d,0x42,0xee,0x45,0x09,0x14,
        0x99,0x5e,0xdf,0x73,0xef,0xa5,0xe5,0xe7,
        0xf6,0xbc,0x4b,0x16,0x87,0xbe,0x6a,0x0c,
        0xf4,0x0f,0xab,0x91,0x5d,0x76,0x57,0xbd,
        0x0a,0xfe,0x59,0xb8,0xde,0xcf,0x07,0xcc,
        0x7e,0xc6,0xb7,0xd6,0xbe,0x22,0x48,0x9a,
        0x87,0x4e,0xb7,0xef,0xda,0x3b,0x65,0xd4,
        0x65,0x77,0xa7,0xce,0x2a,0x42,0x31,0x76,
        0xf8,0xad,0x38,0xa0,0xea,0xd6,0x70,0xde,
        0xd8,0xc7,0x0e,0xdb,0x8d,0x45,0x43,0xc0,
        0xb3,0x0e,0x29,0x5a,0x76,0x9e,0xfa,0xd5,
        0xb7,0x6e,0x4d,0x00,0xe4,0x0e,0x2d,0x93,
        0xdb,0xca,0x69,0x68,0x8e,0xa1,0xf0,0x97
    }
};

/***
SceNpCommunicationSignature

b9dde13b0100000000000000a2f2d66966b3f8d64f9c7dc9fa81e8fdd335cfa7b4b0b1dca063cf38f7dc3a46bad2dbf90dbd293f146165764419818cf74d9612680ec39bd3dbc02c3f87dc36a5721baea8ead5085ba7c89e77d29577ad157cd610c1f5b380783070b51dbeb37eec58387f707d89879fac90358847dbe9a912929ad92a92c01f8bfc1d788e5aeea145a44892f8cb5d198d2bbf54ec783952deee
***/

static const SceNpCommunicationSignature s_npCommunicationSignature = {
    {
        0xb9,0xdd,0xe1,0x3b,0x01,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0xa2,0xf2,0xd6,0x69,
        0x66,0xb3,0xf8,0xd6,0x4f,0x9c,0x7d,0xc9,
        0xfa,0x81,0xe8,0xfd,0xd3,0x35,0xcf,0xa7,
        0xb4,0xb0,0xb1,0xdc,0xa0,0x63,0xcf,0x38,
        0xf7,0xdc,0x3a,0x46,0xba,0xd2,0xdb,0xf9,
        0x0d,0xbd,0x29,0x3f,0x14,0x61,0x65,0x76,
        0x44,0x19,0x81,0x8c,0xf7,0x4d,0x96,0x12,
        0x68,0x0e,0xc3,0x9b,0xd3,0xdb,0xc0,0x2c,
        0x3f,0x87,0xdc,0x36,0xa5,0x72,0x1b,0xae,
        0xa8,0xea,0xd5,0x08,0x5b,0xa7,0xc8,0x9e,
        0x77,0xd2,0x95,0x77,0xad,0x15,0x7c,0xd6,
        0x10,0xc1,0xf5,0xb3,0x80,0x78,0x30,0x70,
        0xb5,0x1d,0xbe,0xb3,0x7e,0xec,0x58,0x38,
        0x7f,0x70,0x7d,0x89,0x87,0x9f,0xac,0x90,
        0x35,0x88,0x47,0xdb,0xe9,0xa9,0x12,0x92,
        0x9a,0xd9,0x2a,0x92,0xc0,0x1f,0x8b,0xfc,
        0x1d,0x78,0x8e,0x5a,0xee,0xa1,0x45,0xa4,
        0x48,0x92,0xf8,0xcb,0x5d,0x19,0x8d,0x2b,
        0xbf,0x54,0xec,0x78,0x39,0x52,0xde,0xee
    }
};
#endif /* __SCE_NP_CONF_H__ */