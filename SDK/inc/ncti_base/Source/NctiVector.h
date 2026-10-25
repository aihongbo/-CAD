#ifndef NctiVector_H
#define NctiVector_H
#include <math.h>
#include "ncti_base.h"
#include "NctiPosition.h"
namespace NCTI
{
    class NctiMatrix;
    NctiVector operator*(NctiVector const& vec1_, NctiVector const& vec2_);
	/**
	* @brief NctiVector
	* @see NctiDummyBaseClass
	*/
    class DECL_NCTI_BASE NctiVector : public NCTI::NctiDummyBaseClass
    {
    public:
        Ncti_Double comp[3]{};
        friend NctiVector operator-(NctiVector const&);
        friend NctiVector operator+(NctiVector const&, NctiVector const&);
        friend NctiVector operator-(NctiVector const&, NctiVector const&);
        friend Ncti_Double operator%(NctiVector const&, NctiVector const&);
        friend Ncti_Double operator%(NctiPosition const&, NctiVector const&);
        friend Ncti_Double operator%(NctiVector const&, NctiPosition const&);
        friend Ncti_Double operator%(NctiPosition const&, NctiUnitVector const&);
        friend Ncti_Double operator%(NctiUnitVector const&, NctiPosition const&);
        friend NctiVector operator*(NctiVector const&, NctiVector const&);
        friend NctiVector operator*(Ncti_Double, NctiVector const&);
        friend NctiVector operator*(NctiVector const&, Ncti_Double);
        friend NctiVector operator/(NctiVector const&, Ncti_Double);
        //NCTI_RESNOR
        friend DECL_NCTI_BASE bool parallel(NctiUnitVector const& uVec_, NctiVector const& vec_, const Ncti_Double d_);
        friend DECL_NCTI_BASE NctiVector operator*(NctiMatrix const& mat_, NctiVector const& vec_);
        friend DECL_NCTI_BASE NctiVector operator*(NctiVector const& vec_, NctiMatrix const& mat_);
        friend DECL_NCTI_BASE bool same_vector(NctiVector const& vec1_, NctiVector const& vec2_, const Ncti_Double res);
        friend std::ostream& operator<<(std::ostream& os, const NctiVector& vec)
        {
            os << "NctiVector(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
            return os;
        }
    public:
        NctiVector() {};
        NctiVector(const Ncti_Double*v) {
            comp[0] = v[0];
            comp[1] = v[1];
            comp[2] = v[2];
        };
        NctiVector(const float* v) {
            comp[0] = v[0];
            comp[1] = v[1];
            comp[2] = v[2];
        };
        operator Ncti_Double* () { return comp; }
        operator const Ncti_Double* ()const { return comp; }
        NctiVector(Ncti_Double x, Ncti_Double y, Ncti_Double z) {
            comp[0] = x;
            comp[1] = y;
            comp[2] = z;
        }

        NctiVector(NctiVector const& vec_) {
            comp[0] = vec_.comp[0];
            comp[1] = vec_.comp[1];
            comp[2] = vec_.comp[2];
        }
        inline Ncti_Double x() const
        {
            return comp[0];
        }
        inline Ncti_Double y() const
        {
            return comp[1];
        }
        inline Ncti_Double z() const
        {
            return comp[2];
        }
        inline Ncti_Double component(int i) const
        {
            return comp[i];
        }
        inline Ncti_Double& x()
        {
            return comp[0];
        }
        inline Ncti_Double& y()
        {
            return comp[1];
        }
        inline Ncti_Double& z()
        {
            return comp[2];
        }

        inline Ncti_Float fx() const
        {
            return (Ncti_Float)comp[0];
        }
        inline Ncti_Float fy() const
        {
            return (Ncti_Float)comp[1];
        }
        inline Ncti_Float fz() const
        {
            return (Ncti_Float)comp[2];
        }

        inline Ncti_Float fx()
        {
            return (Ncti_Float)comp[0];
        }
        inline Ncti_Float fy()
        {
            return (Ncti_Float)comp[1];
        }
        inline Ncti_Float fz()
        {
            return (Ncti_Float)comp[2];
        }
        inline void set_x(Ncti_Double new_x) { comp[0] = new_x; }
        inline void set_y(Ncti_Double new_y) { comp[1] = new_y; }
        inline void set_z(Ncti_Double new_z) { comp[2] = new_z; }
        inline NctiVector const& operator+=(NctiVector const& vec_)
        {
            comp[0] += vec_.comp[0];
            comp[1] += vec_.comp[1];
            comp[2] += vec_.comp[2];
            return *this;
        }
        inline NctiVector const& operator+=(NctiPosition const& vec_)
        {
            comp[0] += vec_.coord[0];
            comp[1] += vec_.coord[1];
            comp[2] += vec_.coord[2];
            return *this;
        }
        inline NctiVector const& operator-=(NctiVector const& vec_)
        {
            comp[0] -= vec_.comp[0];
            comp[1] -= vec_.comp[1];
            comp[2] -= vec_.comp[2];
            return *this;
        }
        inline NctiVector const& operator-=(NctiPosition const& vec_)
        {
            comp[0] -= vec_.coord[0];
            comp[1] -= vec_.coord[1];
            comp[2] -= vec_.coord[2];
            return *this;
        }
        inline NctiVector const& operator*=(Ncti_Double d)
        {
            comp[0] *= d;
            comp[1] *= d;
            comp[2] *= d;
            return *this;
        }
        inline NctiVector const& operator/=(Ncti_Double d)
        {
            comp[0] /= d;
            comp[1] /= d;
            comp[2] /= d;
            return *this;
        }
        inline Ncti_Double len_sq() const
        {
            Ncti_Double dp;
            dp = comp[0] * comp[0], dp += comp[1] * comp[1], dp += comp[2] * comp[2];
            return dp;
        }

        inline Ncti_Double len() const
        {
            Ncti_Double dp = len_sq();
            return (dp>0?sqrt(dp):0);
        }

        inline NctiVector normlize()const {
            return (*this) / len();
        }

        NctiVector const& operator*=(NctiTransf const& t);
        NctiVector const& operator *=(NctiMatrix const& m);

        double dot(const NctiVector& i_vec) const;
        NctiVector cross(const NctiVector& i_vec) const;
    };

    inline bool operator!=(NctiVector const& p1, NctiVector const& p2)
    {
        Ncti_Double d1 = fabs(p1.comp[0] - p2.comp[0]);
        if (d1 > NCTI_RESABS) return true;
        Ncti_Double d2 = fabs(p1.comp[1] - p2.comp[1]);
        if (d2 > NCTI_RESABS) return true;
        Ncti_Double d3 = fabs(p1.comp[2] - p2.comp[2]);
        if (d3 > NCTI_RESABS) return true;
        return !(d1 * d1 + d2 * d2 + d3 * d3 <= NCTI_RESABS * NCTI_RESABS);

        //return !same_point(p1, p2, NCTI_RESABS);
    }

    inline bool operator==(NctiVector const& p1, NctiVector const& p2)
    {
        Ncti_Double d1 = fabs(p1.comp[0] - p2.comp[0]);
        if (d1 > NCTI_RESABS) return false;
        Ncti_Double d2 = fabs(p1.comp[1] - p2.comp[1]);
        if (d2 > NCTI_RESABS) return false;
        Ncti_Double d3 = fabs(p1.comp[2] - p2.comp[2]);
        if (d3 > NCTI_RESABS) return false;
        return (d1 * d1 + d2 * d2 + d3 * d3 <= NCTI_RESABS * NCTI_RESABS);
    }

    inline NctiVector operator+(NctiVector const& vec1_, NctiVector const& vec2_)
    {
        return NctiVector(vec1_.comp[0] + vec2_.comp[0],
            vec1_.comp[1] + vec2_.comp[1],
            vec1_.comp[2] + vec2_.comp[2]
        );
    }
    inline NctiVector operator-(NctiVector const& vec1_, NctiVector const& vec2_)
    {
        return NctiVector(vec1_.comp[0] - vec2_.comp[0],
            vec1_.comp[1] - vec2_.comp[1],
            vec1_.comp[2] - vec2_.comp[2]);
    }
    inline NctiVector operator*(Ncti_Double d, NctiVector const& vec_)
    {
        return NctiVector(
            d * vec_.comp[0],
            d * vec_.comp[1],
            d * vec_.comp[2]
        );
    }
    inline NctiVector operator*(NctiVector const& vec_, Ncti_Double d)
    {
        return NctiVector(
            d * vec_.comp[0],
            d * vec_.comp[1],
            d * vec_.comp[2]
        );
    }
    inline NctiVector operator/(NctiVector const& vec_, Ncti_Double d)
    {
        return NctiVector(vec_.comp[0] / d, vec_.comp[1] / d, vec_.comp[2] / d);
    }
    inline NctiVector operator-(NctiVector const& vec_)
    {
        return NctiVector(-vec_.comp[0], -vec_.comp[1], -vec_.comp[2]);
    };
    inline Ncti_Double operator%(NctiVector const& vec1_, NctiVector const& vec2_)
    {
        Ncti_Double dp;
        dp = vec1_.comp[0] * vec2_.comp[0], dp += vec1_.comp[1] * vec2_.comp[1], dp += vec1_.comp[2] * vec2_.comp[2];
        return dp;
    }
    inline Ncti_Double operator%(NctiPosition const& p, NctiVector const& vec_)
    {
        Ncti_Double dp;
        dp = p.coord[0] * vec_.comp[0], dp += p.coord[1] * vec_.comp[1], dp += p.coord[2] * vec_.comp[2];
        return dp;
    }
    inline Ncti_Double operator%(NctiVector const& vec_, NctiPosition const& p)
    {
        Ncti_Double dp;
        dp = p.coord[0] * vec_.comp[0], dp += p.coord[1] * vec_.comp[1], dp += p.coord[2] * vec_.comp[2];
        return dp;
    }
    inline NctiVector operator*(NctiVector const& vec1_, NctiVector const& vec2_)
    {
        return NctiVector(
            vec1_.comp[1] * vec2_.comp[2] - vec1_.comp[2] * vec2_.comp[1],
            vec1_.comp[2] * vec2_.comp[0] - vec1_.comp[0] * vec2_.comp[2],
            vec1_.comp[0] * vec2_.comp[1] - vec1_.comp[1] * vec2_.comp[0]);
    }
    inline NctiVector operator-(NctiPosition const& p1, NctiPosition const& p2)
    {
        return NctiVector(
            p1.x() - p2.x(),
            p1.y() - p2.y(),
            p1.z() - p2.z()
        );
    }
    inline NctiPosition operator+(NctiVector const& vec_, NctiPosition const& p)
    {
        return p + vec_;
    }
    inline NctiPosition operator+(NctiPosition const& p, NctiVector const& vec_)
    {
        return NctiPosition(
            p.x() + vec_.x(),
            p.y() + vec_.y(),
            p.z() + vec_.z()
        );
    }
    inline NctiPosition operator-(NctiPosition const& p, NctiVector const& vec_)
    {
        return NctiPosition(
            p.x() - vec_.x(),
            p.y() - vec_.y(),
            p.z() - vec_.z()
        );
    }
    DECL_NCTI_BASE bool parallel(NctiUnitVector const& uVec_, NctiVector const& vec_, const Ncti_Double d_);
}

namespace std {
    template<>
    struct hash<NCTI::NctiVector> {
        size_t operator()(const NCTI::NctiVector& p) const noexcept {
            std::size_t seed = 0;
            hash_combine(seed, p.x());
            hash_combine(seed, p.y());
            hash_combine(seed, p.z());
            return seed;
        }
    };
}

#endif // !NctiVector_H
