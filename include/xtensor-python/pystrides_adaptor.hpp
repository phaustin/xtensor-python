/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef PYSTRIDES_ADAPTOR_HPP
#define PYSTRIDES_ADAPTOR_HPP

#include <cstddef>
#include <iterator>

namespace xt
{

    template <std::size_t N>
    class pystrides_iterator;

    template <std::size_t N>
    class pystrides_adaptor
    {

    public:

        using value_type = std::size_t;
        using const_reference = value_type;
        using const_pointer = const value_type*;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        using const_iterator = pystrides_iterator<N>;

        pystrides_adaptor() = default;
        pystrides_adaptor(const_pointer data, size_type size);

        bool empty() const noexcept;
        size_type size() const noexcept;

        const_reference operator[](size_type i) const;

        const_reference front() const;
        const_reference back() const;

        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;

    private:

        const_pointer p_data;
        size_type m_size;
    };

    /*************************************
     * pystrides_iterator implementation *
     *************************************/

    template <std::size_t N>
    class pystrides_iterator
    {

    public:

        using self_type = pystrides_iterator<N>;

        using value_type = typename pystrides_adaptor<N>::value_type;
        using pointer = typename pystrides_adaptor<N>::const_pointer;
        using reference = typename pystrides_adaptor<N>::const_reference;
        using difference_type = typename pystrides_adaptor<N>::difference_type;
        using iterator_category = std::random_access_iterator_tag;

        inline pystrides_iterator(pointer current)
            : p_current(current)
        {
        }

        inline reference operator*() const { return *p_current / N; }
        inline pointer operator->() const { return p_current; }

        inline reference operator[](difference_type n) { return *(p_current + n) / N; }

        inline self_type& operator++() { ++p_current; return *this; }
        inline self_type& operator--() { --p_current; return *this; }

        inline self_type operator++(int) { self_type tmp(*this); ++p_current; return tmp; }
        inline self_type operator--(int) { self_type tmp(*this); --p_current; return tmp; }

        inline self_type& operator+=(difference_type n) { p_current += n; return *this; }
        inline self_type& operator-=(difference_type n) { p_current -= n; return *this; }

        inline self_type operator+(difference_type n) const { return self_type(p_current + n); }
        inline self_type operator-(difference_type n) const { return self_type(p_current - n); }
        inline self_type operator-(const self_type& rhs) const
        {
            self_type tmp(*this);
            tmp -= (p_current - rhs.p_current);
            return tmp;
        }

        pointer get_pointer() const { return p_current; }

    private:

        pointer p_current;
    };

    template <std::size_t N>
    inline bool operator==(const pystrides_iterator<N>& lhs,
                           const pystrides_iterator<N>& rhs)
    {
        return lhs.get_pointer() == rhs.get_pointer();
    }

    template <std::size_t N>
    inline bool operator!=(const pystrides_iterator<N>& lhs,
                           const pystrides_iterator<N>& rhs)
    {
        return !(lhs == rhs);
    }

    template <std::size_t N>
    inline bool operator<(const pystrides_iterator<N>& lhs,
                          const pystrides_iterator<N>& rhs)
    {
        return lhs.get_pointer() < rhs.get_pointer();
    }

    template <std::size_t N>
    inline bool operator<=(const pystrides_iterator<N>& lhs,
                           const pystrides_iterator<N>& rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }

    template <std::size_t N>
    inline bool operator>(const pystrides_iterator<N>& lhs,
                          const pystrides_iterator<N>& rhs)
    {
        return !(lhs <= rhs);
    }

    template <std::size_t N>
    inline bool operator>=(const pystrides_iterator<N>& lhs,
                           const pystrides_iterator<N>& rhs)
    {
        return !(lhs < rhs);
    }

    /************************************
     * pystrides_adaptor implementation *
     ************************************/

    template <std::size_t N>
    inline pystrides_adaptor<N>::pystrides_adaptor(const_pointer data, size_type size)
        : p_data(data), m_size(size)
    {
    }

    template <std::size_t N>
    inline bool pystrides_adaptor<N>::empty() const noexcept
    {
        return m_size == 0;
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::size() const noexcept -> size_type
    {
        return m_size;
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::operator[](size_type i) const -> const_reference
    {
        return p_data[i] / N;
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::front() const -> const_reference
    {
        return p_data[0] / N;
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::back() const -> const_reference
    {
        return p_data[m_size - 1] / N;
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::begin() const -> const_iterator
    {
        return const_iterator(p_data);
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::end() const -> const_iterator
    {
        return const_iterator(p_data + m_size);
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::cbegin() const -> const_iterator
    {
        return begin();
    }

    template <std::size_t N>
    inline auto pystrides_adaptor<N>::cend() const -> const_iterator
    {
        return end();
    }

}

#endif

