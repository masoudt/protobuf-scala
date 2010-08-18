CC=g++
OUT=protoc-gen-scala

SRCDIR=./src/org/matmexrhino/protobuf/scala

compile:
	for SRC in `ls ${SRCDIR}/*.cc`; do \
	${CC} -c -O2 -Iinclude  -Isrc -o target/`basename $${SRC} .cc`.o $${SRC} ; \
	done

build: compile
	${CC} `ls target/*.o|xargs` -lprotoc -lprotobuf -o target/${OUT}

clean:
	rm target/*.o

distclean:
	rm target/*