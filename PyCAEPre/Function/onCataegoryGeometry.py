#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright (c) 2025 粤港澳大湾区（广东）国创中心
PyCAEPre is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
"""

from scripts.Geometry.pyncti_create_box import pyncti_create_box
from scripts.Geometry.pyncti_create_cylinder import pyncti_create_cylinder
from scripts.Geometry.pyncti_boolean import pyncti_boolean 
from scripts.Geometry.pyncti_fillet import pyncti_fillet
from scripts.Geometry.pyncti_chamfer import pyncti_chamfer
from scripts.Geometry.pyncti_pan import pyncti_pan
from scripts.Geometry.pyncti_scale import pyncti_scale
from scripts.Geometry.pyncti_rotate import pyncti_rotate
from scripts.Geometry.pyncti_remove_feature import pyncti_remove_feature
from scripts.Geometry.pyncti_remove_face import pyncti_remove_face
from scripts.Geometry.pyncti_extract_cell import  pyncti_extract_cell
from scripts.Geometry.pyncti_fill_loop import pyncti_fill_loop
from scripts.Geometry.pyncti_create_compound import pyncti_create_compound
from scripts.Geometry.pyncti_sewing_bodies import pyncti_sewing_bodies
from scripts.Geometry.pyncti_split_face import pyncti_split_face
from scripts.Geometry.pyncti_prism import pyncti_prism
from scripts.Geometry.pyncti_geo_periodic import pyncti_geo_periodic
from scripts.Geometry.pyncti_rotate_periodic import pyncti_rotate_periodic
from scripts.Geometry.pyncti_find_small_feature import pyncti_find_small_feature
from scripts.Geometry.pyncti_find_fillets import pyncti_find_fillets
from scripts.Geometry.pyncti_find_logos import pyncti_find_logos
from scripts.Geometry.pyncti_find_holes import pyncti_find_holes
from scripts.Geometry.pyncti_explode_body import pyncti_explode_body
from scripts.Geometry.pyncti_patching_face import pyncti_patching_face

def on_exec_box_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_create_box(self.NCTI,self.doc)
    self.updateTree()

def on_exec_cylinder_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_create_cylinder(self.NCTI,self.doc)
    self.updateTree()

def on_exec_boole_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_boolean(self.NCTI,self.doc)
    self.updateTree()

def on_exec_fillet_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_fillet(self.NCTI,self.doc)

def on_exec_chamfer_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_chamfer(self.NCTI,self.doc)

def on_exec_pan_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_pan(self.NCTI,self.doc)

def on_exec_scale_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_scale(self.NCTI,self.doc)

def on_exec_rotate_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_rotate(self.NCTI,self.doc)

def on_exec_removefeature_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_remove_feature(self.NCTI,self.doc)

def on_exec_removeface_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_remove_face(self.NCTI,self.doc)

def on_exec_extractcell_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_extract_cell(self.NCTI,self.doc)

def on_exec_fillloop_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_fill_loop(self.NCTI,self.doc)

def on_exec_createcompound_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_create_compound(self.NCTI,self.doc)
    self.updateTree()

def on_exec_explodeboldy_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_explode_body(self.NCTI,self.doc)
    self.updateTree()

def on_exec_sewingbodies_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_sewing_bodies(self.NCTI,self.doc)
    self.updateTree()

def on_exec_splitface_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_split_face(self.NCTI,self.doc)
    self.updateTree()

def on_exec_prism_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_prism(self.NCTI,self.doc)

def on_exec_patching_face_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_patching_face(self.NCTI,self.doc,thruSection=True)

def on_exec_geoperiodic_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_geo_periodic(self.NCTI,self.doc)
    self.updateTree()

def on_exec_rotateperiodic_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_rotate_periodic(self.NCTI,self.doc)
    self.updateTree()
    

def extract_numbers_with_keys(data_dict,event = None):
    for key, value in data_dict.items():
        flat_list = [item for sublist in value for item in sublist]
        yield key, flat_list

def on_exec_findsmallfeature_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_find_small_feature(self.NCTI,self.doc)

def on_exec_findfillets_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_find_fillets(self.NCTI,self.doc)

def on_exec_findlogos_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_find_logos(self.NCTI,self.doc)

#查找孔洞
def on_exec_findholes_button_click(self,event = None):
    if False == hasattr(self, 'doc'):
        return
    pyncti_find_holes(self.NCTI,self.doc)
    