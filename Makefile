
RELEASE=2.65

tarball:
	git archive --format=tar --prefix=tree-${RELEASE}/ HEAD | gzip > ${HOME}/tmp/tree-${RELEASE}.tar.gz

test_tree: test_tree.o 
	g++ -o test_tree test_tree.o
