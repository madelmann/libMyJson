
EXCLUDE=*.sh
RELEASE="libMyJson-`cat version`_`svnversion`.tar.gz"

echo "Packing files for release ${RELEASE} ..."

tar cfvz ${RELEASE} --exclude=${EXCLUDE} *

echo "done."

