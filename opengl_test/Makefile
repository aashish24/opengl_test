all: dlist

dlist: dlist.C readGL.C
	g++  -I ${TACC_BOOST_INC} -O -o nompidl  dlist.C readGL.C -lX11 -lGL
	mpicxx -I ${TACC_BOOST_INC} -O  -o mpidl dlist.C readGL.C -lX11 -lGL

