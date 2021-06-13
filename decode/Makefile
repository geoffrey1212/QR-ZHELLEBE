CC= gcc #-fsanitize=address
CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O2 -g
LDFLAGS=
LDLIBS=`pkg-config --libs sdl2` -lSDL2_image -lm

DMSRC= source/Resources/d_main.c source/Resources/freect.c

# Decoding code
ASRC= source/Resources/analysis/analysis.c
MESRC= source/Resources/msg_encoding/encode.c source/Resources/msg_encoding/encode_message.c source/Resources/msg_encoding/weaver.c
DSRC= source/Resources/draw/draw.c source/Resources/draw/fill_mat.c source/Resources/draw/mask.c
GSRC= source/Resources/gen_img/gen_img.c
RSSRC= source/Resources/error_cor/RS/array.c source/Resources/error_cor/RS/op.c source/Resources/error_cor/RS/encode_RS.c source/Resources/error_cor/RS/decode_RS.c
SSRC= source/sdl/mysdl.c
MDSRC= source/Resources/msg_decoding/decode.c source/Resources/msg_decoding/unweaver.c source/Resources/msg_decoding/decode_message.c

# Segmentation code
IPSRC= source/preproc/preproc.c
SGSRC= source/segmentation/fpfind.c source/segmentation/FPValid.c source/segmentation/geotrans.c source/segmentation/aploc.c source/segmentation/apsamp.c source/segmentation/extcode.c source/segmentation/surfdraw.c
BSSRC= source/segmentation/proc_code.c source/segmentation/color_mat.c source/segmentation/demask.c source/segmentation/bit_ext.c
MSSRC= source/segmentation/segmentation.c

# Decoding objects
DOBJ=${DMSRC:.c=.o} ${MSRC:.c=.o} ${ASRC:.c=.o} ${MESRC:.c=.o} ${DSRC:.c=.o} ${GSRC:.c=.o} ${RSSRC:.c=.o} ${SSRC:.c=.o} ${MDSRC:.c=.o} ${IPSRC:.c=.o} ${SGSRC:.c=.o} ${BSSRC:.c=.o} ${MSSRC:.c=.o}
DDEP=${DMSRC:.c=.d} ${MSRC:.c=.d} ${ASRC:.c=.d} ${MESRC:.c=.d} ${DSRC:.c=.d} ${GSRC:.c=.d} ${RSSRC:.c=.d} ${SSRC:.c=.d} ${MDSRC:.c=.d} ${IPSRC:.c=.d} ${SGSRC:.c=.d} ${BSSRC:.c=.d} ${MSSRC:.c=.d}


all : decode


decode: ${DOBJ}
	${CC} ${CFLAGS} ${CPPFLAGS} ${DOBJ} ${LDLIBS} -o decode


.PHONY: clean

clean:
	${RM} ${DOBJ} ${DDEP} *-
	${RM}  decode
	${RM} *.d

-include ${DEP} ${DDEP}
