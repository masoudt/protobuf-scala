CC=g++
OUT=protoc.exe  # change this for your env, configure later.

SRCDIR=./src/org/matmexrhino/protobuf/scala

compile:
	for SRC in `ls ${SRCDIR}/*.cc`; do \
	${CC} -c -O2 -Iinclude -Isrc -o target/`basename $${SRC} .cc`.o $${SRC} ; \
	done

build: compile
	${CC} `ls target/*.o|xargs` -Llib -lprotoc -lprotobuf -o target/${OUT}

clean:
	rm target/*.o

distclean:
	rm target/*