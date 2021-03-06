itk_module_test()
set(ITK-IO-TIFFTests
itkTIFFImageIOTest.cxx
itkIOTIFFHeaderTest.cxx
)

CreateTestDriver(ITK-IO-TIFF  "${ITK-IO-TIFF-Test_LIBRARIES}" "${ITK-IO-TIFFTests}")

add_test(NAME itkIOTIFFHeaderTest
      COMMAND ITK-IO-TIFFTestDriver itkIOTIFFHeaderTest)
add_test(NAME itkTIFFImageIOTest
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/cthead1.tif
              ${ITK_TEST_OUTPUT_DIR}/cthead1.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/cthead1.tif ${ITK_TEST_OUTPUT_DIR}/cthead1.tif)
add_test(NAME itkTIFFImageIOTest1
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImage.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImage.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImage.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImage.tif)
add_test(NAME itkTIFFImageIOTest2
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageCCITTFax3.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax3.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageCCITTFax3.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax3.tif)
add_test(NAME itkTIFFImageIOTest3
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageCCITTFax4.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax4.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageCCITTFax4.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax4.tif)
add_test(NAME itkTIFFImageIOTest4
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageGray.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageGray.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageGray.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageGray.tif)
add_test(NAME itkTIFFImageIOTest5
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageHuffmanRLE.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageHuffmanRLE.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageHuffmanRLE.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageHuffmanRLE.tif)
add_test(NAME itkTIFFImageIOTest6
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageJPEG.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageJPEG.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageJPEG.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageJPEG.tif)
add_test(NAME itkTIFFImageIOTest7
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageLZW.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageLZW.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageLZW.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageLZW.tif)
add_test(NAME itkTIFFImageIOTest8
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageNone.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageNone.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageNone.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageNone.tif)
add_test(NAME itkTIFFImageIOTest9
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImagePackBits.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImagePackBits.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImagePackBits.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImagePackBits.tif)
add_test(NAME itkTIFFImageIOTest10
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageZIP.tif
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageZIP.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageZIP.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageZIP.tif)
add_test(NAME itkTIFFImageIOTest11
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/ShortTestImage.tiff
              ${ITK_TEST_OUTPUT_DIR}/ShortTestImage.tiff
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/ShortTestImage.tiff ${ITK_TEST_OUTPUT_DIR}/ShortTestImage.tiff 2 2)
add_test(NAME itkTIFFImageIOTest12
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/48BitTestImage.tif
              ${ITK_TEST_OUTPUT_DIR}/48BitTestImage.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/48BitTestImage.tif ${ITK_TEST_OUTPUT_DIR}/48BitTestImage.tif 2 2)
add_test(NAME itkTIFFImageIOTest13
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageCCITTFax3.mha
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax3.mha
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageCCITTFax3.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax3.mha)
add_test(NAME itkTIFFImageIOTest14
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/RGBTestImageCCITTFax4.mha
              ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax4.mha
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/RGBTestImageCCITTFax4.tif ${ITK_TEST_OUTPUT_DIR}/RGBTestImageCCITTFax4.mha)
add_test(NAME itkTIFFImageIOMultiPagesTest
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/ramp.tif
              ${ITK_TEST_OUTPUT_DIR}/ramp.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/ramp.tif ${ITK_TEST_OUTPUT_DIR}/ramp.tif 3)
add_test(NAME itkTIFFImageIOMultiPagesTest2
      COMMAND ITK-IO-TIFFTestDriver
    --compare ${ITK_DATA_ROOT}/Baseline/IO/rampShort.tif
              ${ITK_TEST_OUTPUT_DIR}/rampShort.tif
    itkTIFFImageIOTest ${ITK_DATA_ROOT}/Input/rampShort.tif ${ITK_TEST_OUTPUT_DIR}/rampShort.tif 3 3)
