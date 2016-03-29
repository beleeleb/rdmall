/*
 *
 *	Yan 23/2/15
 *	Reviewed by: Yael
 *
 */

#ifndef __BITSET_H__
#define __BITSET_H__

#include <iostream>//for cerr prints
#include <bitset>	// for for binary representation when using cerr

#include <algorithm> //for transform
#include <vector> //for vector
#include <cctype>		// for size_t
#include <cassert> //for assert
#include "mydefs.h" //for debug

namespace rd3
{

    /*
     * makes use of bit proxy in order to work
     * Warning! keep in mind that a static array is used here, thus, be aware to set a compatible size.
     */

    template <size_t NBITS>
    class Bitset
    {

        class BitProxy; //don't worry about this. this is only needed for a private implementation of operator[]

    public:
        explicit Bitset(); // using generated CCtor, Dtor & Assignment operator

        bool operator==(const Bitset& o_)const;
        bool operator!=(const Bitset& o_)const;

        Bitset& operator&=(const Bitset& o_);
        Bitset& operator|=(const Bitset& o_);
        Bitset& operator^=(const Bitset& o_);

        Bitset& operator<<=(size_t NumofShifts_);
        Bitset& operator>>=(size_t NumofShifts_);

        Bitset& Flip(size_t index_);
        Bitset& FlipAll();

        size_t CountTrueBits() const;


        inline bool Get(size_t index_) const;
        inline void Set(bool val_, size_t index_);

        inline bool operator[](size_t index_) const;
        inline BitProxy operator[](size_t index_);

        DEBUG_ONLY(void PrintSet() ;)

    private:

        static const size_t BYTE = 8;
        static const size_t ONE = 1;
        static const size_t BLKSZ = BYTE  * sizeof(size_t);
        static const size_t ARRSZ = ((NBITS - 1) / BLKSZ) + 1;

        std::vector <size_t> m_data;

        void CleanBitsIMP() const;

        const size_t BitIdx(const size_t index_) const ;
        const size_t WordIdx(const size_t index_) const ;


        class BitProxy
        {

        public:
            BitProxy(Bitset<NBITS>& bs_, size_t index_);

            bool operator=(bool o_);
            bool operator=(const BitProxy& o_);
            operator bool()const;

        private:
            Bitset<NBITS>& m_bitSet;
            size_t const m_bitIndex;
        }; //end of class BitProxy

        //CLASS FOR BIT COUNTER
        class Counter
        {
        public:
            void operator()(size_t const ptr);

            size_t Result();

        private:
            size_t mycounter;
        }; //end of class Counter

    };//Bitset

    template<size_t NBITS>
    inline const size_t Bitset<NBITS>::BitIdx(const size_t index_) const
    {
        assert(index_ < NBITS && "index higher than NBITS");
        return index_ / BLKSZ;
    }

    template<size_t NBITS>
    inline const size_t Bitset<NBITS>::WordIdx(const size_t index_) const
    {
        assert(index_ < NBITS && "index higher than NBITS");
        return index_ % BLKSZ;
    }


    //BITSHIFT RIGHT------------------------------------------------------------------------------
    template <size_t NBITS>
    inline Bitset<NBITS>& Bitset<NBITS>::operator>>=(size_t NumofShifts_)
    {
        assert(NumofShifts_ < NBITS && "NumofShifts_ higher than NBITS");
        size_t mod  = NumofShifts_ % BLKSZ;
        size_t cell = NumofShifts_ / BLKSZ;

        size_t bit	= !!mod;

        size_t prev = *(m_data.begin() + cell) >> mod;

        cell += bit;

        transform(m_data.begin() + cell , m_data.end() , m_data.begin() ,[&prev, mod](size_t curr)
                  {
                      size_t res = prev | curr << (BLKSZ - mod);
                      prev = curr >> mod;
                      return res;
                  }

                  );

        m_data[ ARRSZ -1 - cell + bit ] = prev;

        std::vector<size_t>::iterator iter = m_data.begin() + ARRSZ - cell + bit;

        transform( iter , m_data.end() , iter , [](size_t){ return 0; } );

        CleanBitsIMP();

        return *this;
    }

    //BITSHIFT LEFT------------------------------------------------------------------------------

    template <size_t NBITS>
    inline Bitset<NBITS>& Bitset<NBITS>::operator<<=(size_t NumofShifts_)
    {
        assert(NumofShifts_ < NBITS && "NumofShifts_ higher than NBITS");

        size_t mod  = NumofShifts_ % BLKSZ;
        size_t cell = NumofShifts_ / BLKSZ;

        size_t bit	= !!mod;

        size_t prev = *(m_data.rbegin() + cell) << mod;

        cell += bit;

        transform(m_data.rbegin() + cell, m_data.rend(), m_data.rbegin(),[&prev, mod] (size_t curr)
                  {
                      size_t res = prev | curr >> (BLKSZ - mod);
                      prev = (curr << mod);
                      return res;
                  }
                  );

        m_data[cell - bit] = prev;

        std::vector<size_t>::iterator iter = m_data.begin() + (cell - bit);

        transform(m_data.begin(), iter ,m_data.begin(), [](size_t){return 0;} );

        CleanBitsIMP();

        return *this;
    }

    //CTOR------------------------------------------------------------------------------
    template <size_t NBITS>
    inline Bitset<NBITS>::Bitset():m_data(ARRSZ, 0)
    {}

    //OP ==------------------------------------------------------------------------------
    template <size_t NBITS>
    inline bool Bitset<NBITS>::operator==(const Bitset& o_)const
    {
        CleanBitsIMP();
        o_.CleanBitsIMP();
        return m_data == o_.m_data;
    }

    //OP !=------------------------------------------------------------------------------
    template <size_t NBITS>
    inline bool Bitset<NBITS>::operator!=(const Bitset& o_)const
    {
        return !(*this== o_);
    }

    //OP &------------------------------------------------------------------------------
    template <size_t NBITS>
    inline Bitset<NBITS>& Bitset<NBITS>::operator&=(const Bitset& o_)
    {

        transform(m_data.begin(), m_data.end(), o_.m_data.begin(), m_data.begin() , std::bit_and<size_t>());

        return *this;
    }

    //OP |------------------------------------------------------------------------------
    template <size_t NBITS>
    inline Bitset<NBITS>& Bitset<NBITS>::operator|=(const Bitset& o_)
    {
        transform(m_data.begin(), m_data.end(), o_.m_data.begin(), m_data.begin() , std::bit_or<size_t>());

        return *this;
    }

    //OP ^------------------------------------------------------------------------------
    template <size_t NBITS>
    inline Bitset<NBITS>& Bitset<NBITS>::operator^=(const Bitset& o_)
    {

        transform(m_data.begin(), m_data.end(), o_.m_data.begin(), m_data.begin() , std::bit_xor<size_t>());

        return *this;
    }

    //FLIP BIT------------------------------------------------------------------------------
    template <size_t NBITS>
    inline Bitset<NBITS>& Bitset<NBITS>::Flip(size_t index_)
    {
        assert(index_ < NBITS && "NumofShifts_ higher than NBITS");
       *(m_data.begin() + BitIdx(index_)) ^= ONE << WordIdx(index_);

        return *this;
    }

    //FLIP ALL------------------------------------------------------------------------------
    template <size_t NBITS>
    inline Bitset<NBITS>& Bitset<NBITS>::FlipAll()
    {
        transform(m_data.begin(), m_data.end(), m_data.begin(), [](size_t ptr){return ~ptr;});
        return *this;
    }

    //GET------------------------------------------------------------------------------
    template <size_t NBITS>
    inline bool Bitset<NBITS>::Get(size_t index_) const
    {
        assert(index_ < NBITS && "NumofShifts_ higher than NBITS");
        return *(m_data.begin() + BitIdx(index_)) & (ONE << WordIdx(index_));
    }

    //SET------------------------------------------------------------------------------
    template <size_t NBITS>
    inline void Bitset<NBITS>::Set(bool val_, size_t index_)
    {
        assert(index_ < NBITS && "NumofShifts_ higher than NBITS");

        size_t *num = &(*(m_data.begin() + BitIdx(index_)));
        *(num) &= ~(ONE << WordIdx(index_));
        *(num) |= (size_t)val_ << WordIdx(index_);

    }

    //template <size_t NBITS>


    //BIT COUNTER------------------------------------------------------------------------------
    template <size_t NBITS>
    inline size_t Bitset<NBITS>::CountTrueBits() const
    {

        return for_each(m_data.begin(), m_data.end(), Counter()).Result();
        CleanBitsIMP();
    }

    //OP [] const------------------------------------------------------------------------------
    template <size_t NBITS>
    inline bool Bitset<NBITS>::operator[](size_t index_) const
    {
        assert(index_ < NBITS && "NumofShifts_ higher than NBITS");

        return Get(index_);
    }

    // ArraySubscript Operator (non-const)-----------------------------------------------------
    template <size_t NBITS>
    inline typename Bitset<NBITS>::BitProxy Bitset<NBITS>::operator[](size_t index_)
    {
        assert(index_ < NBITS && "NumofShifts_ higher than NBITS");

        return  BitProxy(*this, index_);;
    }


    //------------------------------------------------------------------------------
    // BitProxy Constructor
    template <size_t NBITS>
    inline Bitset<NBITS>::BitProxy::BitProxy(Bitset<NBITS>& bs_, size_t index_):m_bitSet(bs_), m_bitIndex(index_)
    {}


    //OP [] non-const------------------------------------------------------------------------------
    template <size_t NBITS>
    inline bool Bitset<NBITS>::BitProxy::operator=(bool o_)
    {
        m_bitSet->Set(o_, m_bitIndex);

        return o_;
    }

    //------------------------------------------------------------------------------
    // const assignment operator
    template <size_t NBITS>
    inline bool Bitset<NBITS>::BitProxy::operator=(const BitProxy& o_)
    {
        bool res = o_.m_bitSet.Get(o_.m_bitIndex);
        m_bitSet->Set(res, m_bitIndex);
        return res;
    }

    //------------------------------------------------------------------------------
    // Conversion from ProxyBit to bool
    template <size_t NBITS>
    inline Bitset<NBITS>::BitProxy::operator bool()const
    {
        return m_bitSet->Get(m_bitIndex);
    }

    template <size_t NBITS>
    inline void Bitset<NBITS>::CleanBitsIMP() const
    {
        size_t* num =  const_cast<size_t*>(&(m_data[ARRSZ - ONE]));

        *num = *num & ((ONE << NBITS / BLKSZ) - ONE);

    }

    template <size_t NBITS>
    void Bitset<NBITS>::Counter::operator()(size_t const ptr)
   {
	   const unsigned char* num = reinterpret_cast<const unsigned char*>(&ptr);

	   static const unsigned char LUT[256] = {

		0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,
		2,3,2,3,3,4,2,3,3,4,3,4,4,5,1,2,2,3,
		2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,
		4,5,3,4,4,5,4,5,5,6,1,2,2,3,2,3,3,4,
		2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,
		4,5,4,5,5,6,2,3,3,4,3,4,4,5,3,4,4,5,
		4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,
		6,7,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
		2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,2,3,
		3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,
		4,5,5,6,4,5,5,6,5,6,6,7,2,3,3,4,3,4,
		4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,
		4,5,5,6,5,6,6,7,3,4,4,5,4,5,5,6,4,5,
		5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,
		6,7,7,8
	   };

	   mycounter += *(LUT + *(num));
	   mycounter += *(LUT + *(++num));
	   mycounter += *(LUT + *(++num));
	   mycounter += *(LUT + *(++num));

#ifdef ENVIRONMENT64

	   mycounter += *(LUT + *(++num));
	   mycounter += *(LUT + *(++num));
	   mycounter += *(LUT + *(++num));
	   mycounter += *(LUT + *(++num));

#endif// LINUX64

   }

    template <size_t NBITS>
    size_t Bitset<NBITS>::Counter::Result()
    {
    	return mycounter;
    }


    //-----------PRINT FUNC FOR DEBUG PURPOSES-------------------------------------------------------------------
    DEBUG_ONLY(

               template<size_t NBITS>
               inline void Bitset<NBITS>::PrintSet()
    {
        std::vector<size_t>::iterator it;

        it = m_data.begin();

        for (; it != m_data.end(); ++it)
        {
            std::bitset<64> binCurr(*it);
            std::cout << binCurr << "-";
        }
    }
               ) //DEBUG_ONLY

    //------------------------------------------------------------------------------
    }//end of namespace rd3
#endif /* __BITSET_H__ */
