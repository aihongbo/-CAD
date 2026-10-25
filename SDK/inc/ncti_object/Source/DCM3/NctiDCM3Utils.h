#ifndef NctiDCMUtils_H
#define NctiDCMUtils_H
#include "dcl_ncti_object.h"
#include "NctiDCM3Def.h"
#include "NctiDCMEXVec3d.h"
namespace NCTI
{
	// Utility functions to generate valid transformation matrices.
	void DECL_NCTI_OBJECT make_transform_mx(double(*o_matrix)[4], double i_dx, double i_dy, double i_dz);
	void DECL_NCTI_OBJECT copy_transform_mx(const double(*i_input)[4], double(*o_copy)[4]);
	void DECL_NCTI_OBJECT normalize_matrix(const double i_mat[4][4], double o_nmat[4][4]);
	void DECL_NCTI_OBJECT identify_matrix(double i_mat[4][4]);
	void DECL_NCTI_OBJECT multi_matrix(const double i_mat1[4][4], const double i_mat2[4][4], double o_mat[4][4]);
	bool DECL_NCTI_OBJECT is_equal_matrix(const double i_mat1[4][4], const double i_mat2[4][4], double i_tol = 1E-8);
	bool DECL_NCTI_OBJECT is_zero_matrix(const double i_mat[4][4], double i_tol = 1E-8);
	bool DECL_NCTI_OBJECT is_identify_matrix(const double i_mat[4][4], double i_tol = 1E-8);

}
#endif