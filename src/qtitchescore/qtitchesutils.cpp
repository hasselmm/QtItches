#include "qtitchesutils.h"

#include "qtitchesmetaenumiterator.h"

namespace QtItches {
namespace Core {

const char *valueToKey(const QMetaObject *metaObject, const char *enumName, int value)
{
    return metaObject->enumerator(metaObject->indexOfEnumerator(enumName)).valueToKey(value);
}

QHash<int, QByteArray> roleNamesFromEnum(const QMetaObject *metaObject, const char *enumName)
{
    const auto metaEnum = metaObject->enumerator(metaObject->indexOfEnumerator(enumName));

    QHash<int, QByteArray> roleNames;
    roleNames.reserve(metaEnum.keyCount());

    for (const auto &member: metaEnum) {
        QByteArray roleName{member.key()};
        roleName[0] = std::tolower(roleName[0]);

        if (roleName.endsWith("Role"))
            roleName.resize(roleName.length() - 4);

        roleNames.insert(member.value(), roleName);
    }

    return roleNames;
}

} // namespace Core
} // namespace QtItches
