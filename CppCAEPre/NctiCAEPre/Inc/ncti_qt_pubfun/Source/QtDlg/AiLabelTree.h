/*
 * Copyright (c) 2025 粤港澳大湾区（广东）国创中心
 *
 * This file is a part of NctiCAEPre.
 *
 * NctiCAEPre is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 */

#ifndef AILABELTREE_H
#define AILABELTREE_H
#include "dcl_ncti_qt_pubfun.h"

#include <vector>
#include <QString>

namespace NCTI 
{
	class DECL_NCTI_QT_PUBFUN AiLabelTree
	{
		
	public:
		AiLabelTree();
		~AiLabelTree();

		QString name;
		std::vector<AiLabelTree> childs;
	};
}

#endif // !AILABELTREE_H

