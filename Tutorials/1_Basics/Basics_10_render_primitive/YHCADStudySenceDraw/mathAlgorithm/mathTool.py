import math

def vector_cross_product(v1, v2):
    """
    计算两个三维矢量的叉乘
    :param v1: 第一个矢量 (x1, y1, z1)
    :param v2: 第二个矢量 (x2, y2, z2)
    :return: 叉乘结果 (x, y, z)
    """
    x = v1[1] * v2[2] - v1[2] * v2[1]
    y = v1[2] * v2[0] - v1[0] * v2[2]
    z = v1[0] * v2[1] - v1[1] * v2[0]
    return (x, y, z)

def vector_magnitude(v):
    """
    计算矢量的模长
    :param v: 矢量 (x, y, z)
    :return: 模长
    """
    return math.sqrt(v[0]**2 + v[1]**2 + v[2]**2)

def normalize_vector(v):
    """
    将矢量单位化
    :param v: 输入矢量 (x, y, z)
    :return: 单位化后的矢量
    """
    magnitude = vector_magnitude(v)
    if magnitude == 0:
        raise ValueError("零矢量无法单位化")
    return (v[0]/magnitude, v[1]/magnitude, v[2]/magnitude)

def point_add_vector(point,vector):
    """
    将点加上一个矢量
    :point v: 输入矢量 (x, y, z)
    :vector v: 输入矢量 (x, y, z)
    :return: 结果点(x,y,z)
    """
    return [point[0]+vector[0],point[1]+vector[1],point[2]+vector[2]]
def multi_vector(dist,vector):
    """
    将标量乘上一个矢量
    :dist v: 输入标量长度
    :vector v: 输入矢量 (x, y, z)
    :return: 结果为新的矢量(x,y,z)
    """
    return [dist*vector.X,dist*vector.Y,dist*vector.Z]