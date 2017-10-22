#include "HomogeneousMaterial.h"
#include "Rotations.h"
#include "Units.h"

class HomogeneousMaterialTest : public ::testing::Test
{
public:
    HomogeneousMaterialTest() {}
    virtual ~HomogeneousMaterialTest() {}
};

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialWithRefIndexAndMagField)
{
    complex_t material_data = complex_t(0.0, 2.0);
    complex_t refIndex = complex_t(1.0 - material_data.real(), material_data.imag());
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMaterial material("MagMaterial", refIndex, magnetism);
    EXPECT_EQ("MagMaterial", material.getName());
    EXPECT_EQ(material_data, material.materialData());
    EXPECT_EQ(magnetism, material.magnetization());

    complex_t material_data2 = complex_t(-1.0, 2.0);
    complex_t refIndex2 = complex_t(1.0 - material_data2.real(), material_data2.imag());
    HomogeneousMaterial material2("MagMaterial", refIndex2, magnetism);
    EXPECT_EQ(material_data2, material2.materialData());

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    HomogeneousMaterial material3("MagMaterial", refIndex2, magnetism2);
    EXPECT_EQ(magnetism2, material3.magnetization());
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialTransform)
{
    complex_t material_data = complex_t(1.0, 0.0);
    complex_t refIndex = complex_t(1.0 - material_data.real(), material_data.imag());
    kvector_t magnetism = kvector_t(0.0, 0.0, 0.0);
    HomogeneousMaterial material("MagMaterial", refIndex, magnetism);

    RotationZ transform(45.*Units::degree);
    HomogeneousMaterial material2 = material.transformedMaterial(transform.getTransform3D());

    EXPECT_EQ("MagMaterial", material2.getName());
    EXPECT_EQ(material_data, material2.materialData());
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialCopy)
{
    complex_t material_data = complex_t(0.0, 2.0);
    complex_t refIndex = complex_t(1.0 - material_data.real(), material_data.imag());
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMaterial material("MagMaterial", refIndex, magnetism);

    HomogeneousMaterial copy = material;

    EXPECT_EQ("MagMaterial", copy.getName());
    EXPECT_EQ(material_data, copy.materialData());
    EXPECT_EQ(magnetism, copy.magnetization());

    RotationZ transform(45.*Units::degree);
    HomogeneousMaterial material2 = copy.transformedMaterial(transform.getTransform3D());

    EXPECT_EQ("MagMaterial", material2.getName());
    EXPECT_EQ(material_data, material2.materialData());
}
