#ifndef QTITCHESMETAENUMITERATOR_H
#define QTITCHESMETAENUMITERATOR_H

#include "qtitchescoreglobal.h"

#include <QMetaEnum>

inline /*constexpr*/ bool operator==(const QMetaEnum &lhs, const QMetaEnum &rhs)
{
    return lhs.enclosingMetaObject() == rhs.enclosingMetaObject() && lhs.name() == rhs.name();
}

namespace QtItches {
namespace Core {

class MetaEnumEntry
{
public:
    MetaEnumEntry() = default;
    constexpr MetaEnumEntry(const QMetaEnum &metaEnum, int index): m_metaEnum{metaEnum}, m_index{index} {}

    const char *key() const { return m_metaEnum.key(m_index); }
    template<typename T = int> T value() const { return static_cast<T>(m_metaEnum.value(m_index)); }

    Q_DECL_RELAXED_CONSTEXPR bool operator==(const MetaEnumEntry &rhs) const { return std::tie(m_metaEnum, m_index) == std::tie(rhs.m_metaEnum, rhs.m_index); }
    Q_DECL_RELAXED_CONSTEXPR bool operator!=(const MetaEnumEntry &rhs) const { return !operator==(rhs); }

    MetaEnumEntry &operator++() { ++m_index; return *this; }

private:
    const QMetaEnum m_metaEnum;
    int m_index;
};

class QTITCHES_CORE_EXPORT MetaEnumIterator : public std::iterator<std::forward_iterator_tag, MetaEnumEntry, int>
{
public:
    MetaEnumIterator() = default;
    constexpr MetaEnumIterator(const QMetaEnum &metaEnum, int index) : m_current{metaEnum, index} {}

    Q_DECL_RELAXED_CONSTEXPR bool operator==(const MetaEnumIterator &rhs) const { return m_current == rhs.m_current; }
    Q_DECL_RELAXED_CONSTEXPR bool operator!=(const MetaEnumIterator &rhs) const { return !operator==(rhs); }

    MetaEnumIterator &operator++() { ++m_current; return *this; }
    const MetaEnumEntry &operator*() const { return m_current; }

private:
    MetaEnumEntry m_current;
};

} // namespace Core
} // namespace QtItches

inline constexpr QtItches::Core::MetaEnumIterator begin(const QMetaEnum &metaEnum) { return {metaEnum, 0}; }
inline /*constexpr*/ QtItches::Core::MetaEnumIterator end(const QMetaEnum &metaEnum) { return {metaEnum, metaEnum.keyCount()}; }

#endif // QTITCHESMETAENUMITERATOR_H
