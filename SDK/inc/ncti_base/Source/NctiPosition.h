#ifndef NctiPosition_H
#define NctiPosition_H
#include "ncti_base.h"
#include <iostream>
#include <sstream>
namespace NCTI
{
    class NctiPosition;
    class NctiVector;
    class NctiUnitVector;
    class NctiMatrix;
    class NctiTransf;
    NctiPosition operator*(NctiPosition const& p, Ncti_Double scale);
    bool operator!=(NctiPosition const& p1, NctiPosition const& p2);
    NctiVector operator-(NctiPosition const& p1, NctiPosition const& p2);
    NctiPosition operator+(NctiPosition const& p, NctiVector const& v);
    NctiPosition operator+(NctiVector const& v, NctiPosition const& p);
    NctiPosition operator-(NctiPosition const& p, NctiVector const& v);
    NctiPosition operator*(NctiPosition const& p, NctiUnitVector const& uv);
    NctiPosition operator*(NctiUnitVector const& uv, NctiPosition const& p);
	/**
	* @brief NctiPosition , it is Ncti_Double coord[3]
	*/
    class DECL_NCTI_BASE NctiPosition : public NCTI::NctiDummyBaseClass
    {
    public:
        Ncti_Double coord[3];
        friend NctiPosition operator*(NctiPosition const&, Ncti_Double);
        friend DECL_NCTI_BASE NctiPosition operator*(NctiMatrix const& m, NctiPosition const& pos);
        friend DECL_NCTI_BASE NctiPosition operator*(NctiPosition const& pos, NctiMatrix const& m);
        friend std::ostream& operator<<(std::ostream& os, const NctiPosition& point)
        {
            os << "NctiPosition(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
            return os;
        }
    public:
        NctiPosition() {
            coord[0] = 0;
            coord[1] = 0;
            coord[2] = 0;
        }
        operator Ncti_Double* () { return coord; }
        operator const Ncti_Double* ()const { return coord; }

        inline NctiPosition(Ncti_Double x, Ncti_Double y, Ncti_Double z) {
            coord[0] = x;
            coord[1] = y;
            coord[2] = z;
        }
        inline NctiPosition(Ncti_Double p[3]) {
            coord[0] = p[0];
            coord[1] = p[1];
            coord[2] = p[2];
        }
        inline NctiPosition(NctiPosition const& p) {
            coord[0] = p.coord[0];
            coord[1] = p.coord[1];
            coord[2] = p.coord[2];
        }
        inline NctiPosition(const Ncti_Float*p) {
            coord[0] = p[0];
            coord[1] = p[1];
            coord[2] = p[2];
        }

        inline Ncti_Double x() const
        {
            return coord[0];
        }
        inline Ncti_Double y() const
        {
            return coord[1];
        }
        inline Ncti_Double z() const
        {
            return coord[2];
        }
        inline Ncti_Double coordinate(int i) const
        {
            return coord[i];
        }
        inline Ncti_Double center()const
        {
            return (coord[0] + coord[1] + coord[2])/3;
        }        
        inline Ncti_Double len()const
        {
            return sqrt(coord[0]* coord[0] + coord[1]* coord[1] + coord[2]* coord[2]);
        }
        inline Ncti_Double& x()
        {
            return coord[0];
        }
        inline Ncti_Double& y()
        {
            return coord[1];
        }
        inline Ncti_Double& z()
        {
            return coord[2];
        }
        inline Ncti_Float fx() const
        {
            return (Ncti_Float)coord[0];
        }
        inline Ncti_Float fy() const
        {
            return (Ncti_Float)coord[1];
        }
        inline Ncti_Float fz() const
        {
            return (Ncti_Float)coord[2];
        }
        inline Ncti_Float fx()
        {
            return (Ncti_Float)coord[0];
        }
        inline Ncti_Float fy()
        {
            return (Ncti_Float)coord[1];
        }
        inline Ncti_Float fz()
        {
            return (Ncti_Float)coord[2];
        }
        inline Ncti_Double& coordinate(int i)
        {
            return coord[i];
        }
        inline void set_x(Ncti_Double new_x) { coord[0] = new_x; }
        inline void set_y(Ncti_Double new_y) { coord[1] = new_y; }
        inline void set_z(Ncti_Double new_z) { coord[2] = new_z; }
        inline void set_coordinate(int i, Ncti_Double new_c)
        {
            coord[i] = new_c;
        }
        inline void set_coordinate(const Ncti_Float *new_c)
        {
            coord[0] = new_c[0];
            coord[1] = new_c[1];
            coord[2] = new_c[2];
        }

        void operator-=(const NctiPosition& new_c) {
            coord[0] -= new_c[0];
            coord[1] -= new_c[1];
            coord[2] -= new_c[2];
        }

        void operator+=(const NctiPosition& new_c) {
            coord[0] += new_c[0];
            coord[1] += new_c[1];
            coord[2] += new_c[2];
        }

        double distance_to(const NctiPosition& other) const {
            double dx = coord[0] - other.coord[0];
            double dy = coord[1] - other.coord[1];
            double dz = coord[2] - other.coord[2];
            auto sum = dx * dx + dy * dy + dz * dz;
            return sum>0?sqrt(sum):0;
        }

        bool operator<(const NctiPosition& o) const;

        friend NctiVector operator-(NctiPosition const& p1, NctiPosition const& p2);
        friend NctiPosition operator*(NctiPosition const& p, Ncti_Double scale);

        friend Ncti_Double operator%(NctiPosition const&, NctiVector const&);
        friend Ncti_Double operator%(NctiVector const&, NctiPosition const&);

        friend Ncti_Double operator%(NctiPosition const&, NctiUnitVector const&);
        friend Ncti_Double operator%(NctiUnitVector const&, NctiPosition const&);

        friend NctiPosition operator*(NctiPosition const&, NctiUnitVector const&);
        friend NctiPosition operator*(NctiUnitVector const&, NctiPosition const&);

        friend NctiPosition interpolate(Ncti_Double param, NctiPosition const& p1, NctiPosition const& p2);
        friend DECL_NCTI_BASE bool same_point(NctiPosition const& p1, NctiPosition const& p2, const Ncti_Double res);
        NctiPosition const& operator*=(NctiMatrix const& m);
        NctiPosition const& operator*=(NctiTransf const& t);

        NctiPosition const& operator+=(NctiVector const& v);
        NctiPosition const& operator-=(NctiVector const& v);
    };


    inline NctiPosition operator+(NctiPosition const& p1, NctiPosition const& p2)
    {
        return NctiPosition(
            p1.x() + p2.x(),
            p1.y() + p2.y(),
            p1.z() + p2.z()
        );
    }

    inline NctiPosition operator/(NctiPosition const& p, Ncti_Double scale)
    {
        return NctiPosition(
            p.coord[0] / scale,
            p.coord[1] / scale,
            p.coord[2] / scale
        );
    }

    inline NctiPosition operator*(NctiPosition const& p, Ncti_Double scale)
    {
        return NctiPosition(
            p.coord[0] * scale,
            p.coord[1] * scale,
            p.coord[2] * scale
        );
    }
    inline bool operator!=(NctiPosition const& p1, NctiPosition const& p2)
    {
        Ncti_Double d1 = fabs(p1.coord[0] - p2.coord[0]);
        if (d1 > NCTI_RESABS) return true;
        Ncti_Double d2 = fabs(p1.coord[1] - p2.coord[1]);
        if (d2 > NCTI_RESABS) return true;
        Ncti_Double d3 = fabs(p1.coord[2] - p2.coord[2]);
        if (d3 > NCTI_RESABS) return true;
        return !(d1 * d1 + d2 * d2 + d3 * d3 <= NCTI_RESABS * NCTI_RESABS);

        //return !same_point(p1, p2, NCTI_RESABS);
    }
    inline bool operator==(NctiPosition const& p1, NctiPosition const& p2)
    {

        Ncti_Double d1 = fabs(p1.coord[0] - p2.coord[0]);
        if (d1 > NCTI_RESABS) return false;
        Ncti_Double d2 = fabs(p1.coord[1] - p2.coord[1]);
        if (d2 > NCTI_RESABS) return false;
        Ncti_Double d3 = fabs(p1.coord[2] - p2.coord[2]);
        if (d3 > NCTI_RESABS) return false;
        return (d1 * d1 + d2 * d2 + d3 * d3 <= NCTI_RESABS * NCTI_RESABS);

        //return same_point(p1, p2, NCTI_RESABS);
    }
    inline NctiPosition interpolate(Ncti_Double param, NctiPosition const& p1, NctiPosition const& p2)
    {
        Ncti_Double inv_param = 1.0 - param;
        return NctiPosition(inv_param * p1.coord[0] + param * p2.coord[0],
            inv_param * p1.coord[1] + param * p2.coord[1],
            inv_param * p1.coord[2] + param * p2.coord[2]);
    }
}

namespace std {
    template<>
    struct hash<NCTI::NctiPosition> {
        size_t operator()(const NCTI::NctiPosition& p) const noexcept {
            std::size_t seed = 0;
            hash_combine(seed, p.x());
            hash_combine(seed, p.y());
            hash_combine(seed, p.z());
            return seed;
        }
    };
}

#endif

