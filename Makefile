
RELEASE=3.1
HTML=${HOME}/public_html/

.PHONY: doc tarball

tarball:
	git archive --format=tar --prefix=tree-${RELEASE}/ HEAD | gzip > ${HOME}/tmp/tree-${RELEASE}.tar.gz

site: tarball doc
	install -d ${HTML}/tree
	install -d ${HTML}/tree/doxygen/html
	install doc/index.html doc/tree.css doc/tree.jpg ChangeLog ${HTML}/tree
	install src/test_tree.cc src/test_tree.output src/tree_example.cc src/tree.hh src/tree_util.hh ${HTML}/tree
	install doxygen/html/* ${HTML}/tree/doxygen/html
	install ${HOME}/tmp/tree-${RELEASE}.tar.gz ${HTML}/tree
	install ${HOME}/tmp/kt_temp/kt_temp_tree/tree.pdf ${HTML}/tree

upload:
	rsync -avz ${HTML}/tree/ zmaya:tree

doc:
	(cd doc; kt -f tree.tex)
	doxygen doc/doxygen_tree.config

test_tree: test_tree.o 
	g++ -o test_tree test_tree.o
