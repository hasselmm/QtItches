#include "qtitchesutils.h"

#include <QMetaEnum>

namespace QtItches {
namespace Core {

const char *valueToKey(const QMetaObject *metaObject, const char *enumName, int value)
{
    return metaObject->enumerator(metaObject->indexOfEnumerator(enumName)).valueToKey(value);
}

QHash<int, QByteArray> roleNamesFromEnum(const QMetaObject *metaObject, const char *enumName)
{
    const auto metaEnum = metaObject->enumerator(metaObject->indexOfEnumerator(enumName));
    const auto keyCount = metaEnum.keyCount();

    QHash<int, QByteArray> roleNames;
    roleNames.reserve(keyCount);

    for (int i = 0; i < keyCount; ++i) {
        QByteArray roleName{metaEnum.key(i)};
        roleName[0] = std::tolower(roleName[0]);

        if (roleName.endsWith("Role"))
            roleName.resize(roleName.length() - 4);

        roleNames.insert(metaEnum.value(i), roleName);
    }

    return roleNames;
}

} // namespace Core
} // namespace QtItches
