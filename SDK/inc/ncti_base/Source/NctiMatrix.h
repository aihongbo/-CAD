#ifndef NctiMatrix_H
#define NctiMatrix_H
#include "ncti_base.h"
#include "NctiVector.h"
namespace NCTI
{
	class NctiTransf;
	class NctiMatrix;
	DECL_NCTI_BASE NctiMatrix operator*(NctiMatrix const & cMatrix1_, NctiMatrix const & cMatrix2_);
	DECL_NCTI_BASE NctiMatrix operator*(Ncti_Double const & dMultiply_, NctiMatrix const & cMatrix_);
	DECL_NCTI_BASE NctiVector operator*(NctiMatrix const & cMatrix_, NctiVector const & vecTarget_);
	DECL_NCTI_BASE NctiVector operator*(NctiVector const & vecTarget_, NctiMatrix const & cMatrix_);
	DECL_NCTI_BASE NctiPosition operator*(NctiMatrix const & cMatrix_, NctiPosition const & posTarget_);
	DECL_NCTI_BASE NctiPosition operator*(NctiPosition const & posTarget_, NctiMatrix const & cMatrix_);
	/**
	* @brief matrix , it is [3][3]
	*/
	class DECL_NCTI_BASE NctiMatrix
	{
	public:
		Ncti_Double elem[3][3] = {0};

		NctiMatrix() {}
		NctiMatrix(NctiVector const & r1_, NctiVector const & r2_, NctiVector const & r3_);

        bool operator==(const NctiMatrix& other) const {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (elem[i][j] != other.elem[i][j]) 
                        return false;
            return true;
        }

		/**
	   * @brief zero the matrix
	   */
		void zero();
		/**
	   * @brief get the matrix value by row and column
	   * @param[in] i_row,
	   * @param[in] i_col,
	   * @return Ncti_Double
	   */
		Ncti_Double element(Ncti_Integer i_row, Ncti_Integer i_col) const
		{
			return elem[i_row][i_col];
		}
		/**
	   * @brief get the matrix vector by column
	   * @param[in] i_col,
	   * @return NctiVector
	   */
		NctiVector column(Ncti_Integer i_col) const
		{
			return NctiVector(elem[0][i_col], elem[1][i_col], elem[2][i_col]);
		}
		/**
	   * @brief get the matrix vector by row
	   * @param[in] i_row,
	   * @return NctiVector
	   */
		NctiVector row(Ncti_Integer i_row) const
		{
			return NctiVector(elem[i_row][0], elem[i_row][1], elem[i_row][2]);
		}
		/**
	   * @brief set the matrix vector by row and column
	   * @param[in] i_row,
	   * @return NctiVector
	   */
		void set_element(Ncti_Integer i_row, Ncti_Integer i_col, Ncti_Double i_new_e)
		{
			elem[i_row][i_col] = i_new_e;
		}
		/**
	   * @brief transpose the matrix
	   * @return NctiMatrix
	   */
		NctiMatrix transpose() const;
		/**
	   * @brief determinant the matrix
	   * @return NctiMatrix
	   */
		Ncti_Double determinant() const;
		/**
	   * @brief inverse the matrix
	   * @return NctiMatrix
	   */
		NctiMatrix inverse() const;
		/**
	   * @brief determine whether is identity
	   * @return Ncti_Boolean
	   */
		Ncti_Boolean is_identity() const;
		NctiMatrix const &operator*=(NctiMatrix const & cMatrix_);
		NctiMatrix const &operator*=(Ncti_Double const & dMultiply_);
		NctiMatrix const &operator*=(NctiTransf const & trans_);
		friend DECL_NCTI_BASE NctiMatrix operator*(NctiMatrix const &, NctiMatrix const &);
		friend DECL_NCTI_BASE NctiMatrix operator*(Ncti_Double const &, NctiMatrix const &);
		friend DECL_NCTI_BASE NctiVector operator*(NctiMatrix const &, NctiVector const &);
		friend DECL_NCTI_BASE NctiVector operator*(NctiVector const &, NctiMatrix const &);
		friend DECL_NCTI_BASE NctiPosition operator*(NctiMatrix const &, NctiPosition const &);
		friend DECL_NCTI_BASE NctiPosition operator*(NctiPosition const &, NctiMatrix const &);
	};
	/**
	* @brief internal use
	*/
	DECL_NCTI_BASE NctiMatrix ncti_scaling(Ncti_Double);
	/**
	* @brief internal use
	*/
	DECL_NCTI_BASE NctiMatrix ncti_rotation(Ncti_Double, NctiVector const &);
}

namespace std {
    template<>
    struct hash<NCTI::NctiMatrix> {
        size_t operator()(const NCTI::NctiMatrix& p) const noexcept {
            std::size_t seed = 0;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    hash_combine(seed, p.elem[i][j]);
            return seed;
        }
    };
}
#endif
