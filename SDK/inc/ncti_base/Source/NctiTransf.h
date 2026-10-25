#ifndef NctiTransf_H
#define NctiTransf_H
#include <stdio.h>
#include "ncti_base.h"
#include "NctiVector.h"
#include "NctiUnitVector.h"
#include "NctiMatrix.h"
#include "NctiPosition.h"
namespace NCTI
{
	class NctiUnitVector;
	DECL_NCTI_BASE NctiTransf RestoreTransf(NctiMatrix const &, NctiVector const &, Ncti_Double,
		Ncti_Boolean, Ncti_Boolean, Ncti_Boolean);
	DECL_NCTI_BASE NctiTransf RotateTransf(Ncti_Double val, NctiVector const &vec);
	DECL_NCTI_BASE NctiTransf TranslateTransf(NctiVector const &vec);
	DECL_NCTI_BASE NctiTransf CoordinateTransf(NctiPosition const &pt, NctiUnitVector const &v1,
		NctiUnitVector const &v2);
	DECL_NCTI_BASE NctiTransf InstanceTransf(
		NctiVector const& dir = {0,0,1}, 
		NctiPosition const& trans = { 0,0,0 },
		Ncti_Double scale = 1);

	DECL_NCTI_BASE NctiTransf operator*(NctiTransf const &t_, NctiTransf const &tran_);
	DECL_NCTI_BASE NctiTransf operator*(NctiTransf const &t_, NctiTransf const *pTransfTarget);
	DECL_NCTI_BASE NctiVector operator*(NctiVector const &v_, NctiTransf const &t);
	DECL_NCTI_BASE NctiUnitVector operator*(NctiUnitVector const &v, NctiTransf const &t);
	DECL_NCTI_BASE NctiPosition operator*(NctiPosition const &p, NctiTransf const &t);

	DECL_NCTI_BASE EnumNctiResult api_convert_transf(const NctiTransf& i_trnsf, Ncti_Double o_matrix[16]);
	DECL_NCTI_BASE EnumNctiResult api_convert_transf(const Ncti_Double i_matrix[16], NctiTransf& o_trnsf);
	DECL_NCTI_BASE EnumNctiResult api_convert_transf(const NctiTransf& i_trnsf, Ncti_Float o_matrix[16]);
    DECL_NCTI_BASE EnumNctiResult api_convert_transf(const NctiTransf& i_trnsf, Ncti_Float o0[4], Ncti_Float o1[4], Ncti_Float o2[4], Ncti_Float o3[4]);
	DECL_NCTI_BASE EnumNctiResult api_convert_transf(const Ncti_Float i_matrix[16], NctiTransf& o_trnsf);
	struct ncti_transf_decompose_data
	{
		Ncti_Double  scalex;
		Ncti_Double  scaley;
		Ncti_Double  scalez;
		Ncti_Double  shearxy;
		Ncti_Double  shearxz;
		Ncti_Double  shearyz;
		Ncti_Double  rotatex;
		Ncti_Double  rotatey;
		Ncti_Double  rotatez;
		Ncti_Double  translatex;
		Ncti_Double  translatey;
		Ncti_Double  translatez;
		Ncti_Double  rotate_radians;
		NctiUnitVector rotate_axis;
	};
	/**
	* @brief NctiTransf
	*/
	class DECL_NCTI_BASE NctiTransf : public NCTI::NctiDummyBaseClass
	{
	public:
		friend class NctiMatrix;
        NctiMatrix affine_part;
        NctiVector translation_part;
        Ncti_Double scaling_part;

	private:
		Ncti_UInteger rotate_flag : 1;
		Ncti_UInteger reflect_flag : 1;
		Ncti_UInteger shear_flag : 1;
		Ncti_UInteger identity_flag : 1;
	public:
		NctiTransf(NctiMatrix const &, NctiVector const &, Ncti_Double,
			Ncti_Boolean, Ncti_Boolean, Ncti_Boolean);
	public:
		NctiTransf();
		NctiTransf(NctiTransf const &t);

        bool operator==(const NctiTransf& other) const {
            if (translation_part != other.translation_part)
                return false;
            if (scaling_part != other.scaling_part)
                return false;
            return affine_part == other.affine_part;
        }

        bool operator!=(NctiTransf const& rhs) const
        {
            return !(*this == rhs);
        }

		void print() const;
		NctiMatrix affine() const;
		NctiVector translation() const;
		Ncti_Double scaling() const
		{
			return /*this == nullptr ? 1 :*/ scaling_part;
		}
		Ncti_Boolean rotate() const
		{
			return /*this == nullptr ? false :*/ rotate_flag;
		}
		Ncti_Boolean reflect() const
		{
			return/* this == nullptr ? false :*/ reflect_flag;
		}
		Ncti_Boolean shear() const
		{
			return /*this == nullptr ? false :*/ shear_flag;
		}
		Ncti_Boolean identity() const
		{
			return /*this == nullptr ? true : */identity_flag;
		}
		/**
	   * @brief create a new NctiTransf
	   * @return NctiTransf
	   */
		friend DECL_NCTI_BASE NctiTransf RestoreTransf(
			NctiMatrix const &,
			NctiVector const &,
			Ncti_Double,
			Ncti_Boolean,
			Ncti_Boolean,
			Ncti_Boolean
		);
		/**
	   * @brief create a new NctiTransf
	   * @param[in] i_dir
	   * @param[in] i_target
	   * @param[in] i_scale
	   * @return NctiTransf
	   */
		friend DECL_NCTI_BASE NctiTransf InstanceTransf(NctiVector const& i_dir , NctiPosition const& i_target ,Ncti_Double i_scale);
		/**
	   * @brief create a new NctiTransf by rotate
	   * @param[in] i_angle
	   * @param[in] i_vec
	   * @return NctiTransf
	   */
		friend DECL_NCTI_BASE NctiTransf RotateTransf(Ncti_Double i_angle, NctiVector const & i_vec);
		/**
	   * @brief create a new NctiTransf by Translate
	   * @param[in] i_vec
	   * @return NctiTransf
	   */
		friend DECL_NCTI_BASE NctiTransf TranslateTransf(NctiVector const & i_vec);
		/**
	   * @brief create a new NctiTransf by Coordinate
	   * @param[in] i_center
	   * @param[in] i_x
	   * @param[in] i_y
	   * @return NctiTransf
	   */
		friend DECL_NCTI_BASE NctiTransf CoordinateTransf(
			NctiPosition const & i_center,
			NctiUnitVector const & i_x,
			NctiUnitVector const & i_y);

		friend DECL_NCTI_BASE NctiTransf operator*(NctiTransf const &, NctiTransf const &);
		friend DECL_NCTI_BASE NctiTransf operator*(
			NctiTransf const & transf,
			NctiTransf const * pTransf2
			)
		{
			return transf * (*pTransf2);
		}
		NctiTransf const &operator*=(NctiTransf const &t);
		NctiTransf inverse() const;
		Ncti_Boolean decompose(ncti_transf_decompose_data& cData) const;
		friend DECL_NCTI_BASE NctiVector operator*(NctiVector const &, NctiTransf const &);
		friend DECL_NCTI_BASE NctiUnitVector operator*(NctiUnitVector const &, NctiTransf const &);
		friend DECL_NCTI_BASE NctiPosition operator*(NctiPosition const &, NctiTransf const &);
		void debug(char const *pszText, FILE * pFilePointer) const;
	};
	extern const DECL_NCTI_BASE NctiTransf ncti_identity_transform;
}

namespace std {
    template<>
    struct hash<NCTI::NctiTransf> {
        size_t operator()(const NCTI::NctiTransf& p) const noexcept {
            std::size_t seed = 0;
            hash_combine(seed, p.affine_part);
            hash_combine(seed, p.translation_part);
            hash_combine(seed, p.scaling_part);
            return seed;
        }
    };
}

#endif
