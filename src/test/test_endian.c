#include <silk/log.h>
#include <silk/endian.h>

void test_endian_read_little()
{
    uint8_t data[] = {
        0x00, 0x11, 0x22, 0x33, 
        0x44, 0x55, 0x66, 0x77, 
        0x88, 0x99, 0xaa, 0xbb, 
        0xcc, 0xdd, 0xee, 0xff
    };

    SILK_ASSERT(silk_endian_read_little16(data) == 0x1100);
    SILK_ASSERT(silk_endian_read_little16(data+1) == 0x2211);
    SILK_ASSERT(silk_endian_read_little16(data+2) == 0x3322);
    SILK_ASSERT(silk_endian_read_little16(data+3) == 0x4433);
    SILK_ASSERT(silk_endian_read_little16(data+4) == 0x5544);
    SILK_ASSERT(silk_endian_read_little16(data+5) == 0x6655);
    SILK_ASSERT(silk_endian_read_little16(data+6) == 0x7766);
    SILK_ASSERT(silk_endian_read_little16(data+7) == 0x8877);
    SILK_ASSERT(silk_endian_read_little16(data+8) == 0x9988);
    SILK_ASSERT(silk_endian_read_little16(data+9) == 0xaa99);
    SILK_ASSERT(silk_endian_read_little16(data+10) == 0xbbaa);
    SILK_ASSERT(silk_endian_read_little16(data+11) == 0xccbb);
    SILK_ASSERT(silk_endian_read_little16(data+12) == 0xddcc);
    SILK_ASSERT(silk_endian_read_little16(data+13) == 0xeedd);
    SILK_ASSERT(silk_endian_read_little16(data+14) == 0xffee);

    SILK_ASSERT(silk_endian_read_little32(data) == 0x33221100);
    SILK_ASSERT(silk_endian_read_little32(data+1) == 0x44332211);
    SILK_ASSERT(silk_endian_read_little32(data+2) == 0x55443322);
    SILK_ASSERT(silk_endian_read_little32(data+3) == 0x66554433);
    SILK_ASSERT(silk_endian_read_little32(data+4) == 0x77665544);
    SILK_ASSERT(silk_endian_read_little32(data+5) == 0x88776655);
    SILK_ASSERT(silk_endian_read_little32(data+6) == 0x99887766);
    SILK_ASSERT(silk_endian_read_little32(data+7) == 0xaa998877);
    SILK_ASSERT(silk_endian_read_little32(data+8) == 0xbbaa9988);
    SILK_ASSERT(silk_endian_read_little32(data+9) == 0xccbbaa99);
    SILK_ASSERT(silk_endian_read_little32(data+10) == 0xddccbbaa);
    SILK_ASSERT(silk_endian_read_little32(data+11) == 0xeeddccbb);
    SILK_ASSERT(silk_endian_read_little32(data+12) == 0xffeeddcc);

    SILK_ASSERT(silk_endian_read_little64(data) == 0x7766554433221100UL);
    SILK_ASSERT(silk_endian_read_little64(data+1) == 0x8877665544332211UL);
    SILK_ASSERT(silk_endian_read_little64(data+2) == 0x9988776655443322UL);
    SILK_ASSERT(silk_endian_read_little64(data+3) == 0xaa99887766554433UL);
    SILK_ASSERT(silk_endian_read_little64(data+4) == 0xbbaa998877665544UL);
    SILK_ASSERT(silk_endian_read_little64(data+5) == 0xccbbaa9988776655UL);
    SILK_ASSERT(silk_endian_read_little64(data+6) == 0xddccbbaa99887766UL);
    SILK_ASSERT(silk_endian_read_little64(data+7) == 0xeeddccbbaa998877UL);
    SILK_ASSERT(silk_endian_read_little64(data+8) == 0xffeeddccbbaa9988UL);
}


void test_endian_read_big()
{
    uint8_t data[] = {
        0x00, 0x11, 0x22, 0x33, 
        0x44, 0x55, 0x66, 0x77, 
        0x88, 0x99, 0xaa, 0xbb, 
        0xcc, 0xdd, 0xee, 0xff
    };

    SILK_ASSERT(silk_endian_read_big16(data) == 0x0011);
    SILK_ASSERT(silk_endian_read_big16(data+1) == 0x1122);
    SILK_ASSERT(silk_endian_read_big16(data+2) == 0x2233);
    SILK_ASSERT(silk_endian_read_big16(data+3) == 0x3344);
    SILK_ASSERT(silk_endian_read_big16(data+4) == 0x4455);
    SILK_ASSERT(silk_endian_read_big16(data+5) == 0x5566);
    SILK_ASSERT(silk_endian_read_big16(data+6) == 0x6677);
    SILK_ASSERT(silk_endian_read_big16(data+7) == 0x7788);
    SILK_ASSERT(silk_endian_read_big16(data+8) == 0x8899);
    SILK_ASSERT(silk_endian_read_big16(data+9) == 0x99aa);
    SILK_ASSERT(silk_endian_read_big16(data+10) == 0xaabb);
    SILK_ASSERT(silk_endian_read_big16(data+11) == 0xbbcc);
    SILK_ASSERT(silk_endian_read_big16(data+12) == 0xccdd);
    SILK_ASSERT(silk_endian_read_big16(data+13) == 0xddee);
    SILK_ASSERT(silk_endian_read_big16(data+14) == 0xeeff);

    SILK_ASSERT(silk_endian_read_big32(data) == 0x00112233);
    SILK_ASSERT(silk_endian_read_big32(data+1) == 0x11223344);
    SILK_ASSERT(silk_endian_read_big32(data+2) == 0x22334455);
    SILK_ASSERT(silk_endian_read_big32(data+3) == 0x33445566);
    SILK_ASSERT(silk_endian_read_big32(data+4) == 0x44556677);
    SILK_ASSERT(silk_endian_read_big32(data+5) == 0x55667788);
    SILK_ASSERT(silk_endian_read_big32(data+6) == 0x66778899);
    SILK_ASSERT(silk_endian_read_big32(data+7) == 0x778899aa);
    SILK_ASSERT(silk_endian_read_big32(data+8) == 0x8899aabb);
    SILK_ASSERT(silk_endian_read_big32(data+9) == 0x99aabbcc);
    SILK_ASSERT(silk_endian_read_big32(data+10) == 0xaabbccdd);
    SILK_ASSERT(silk_endian_read_big32(data+11) == 0xbbccddee);
    SILK_ASSERT(silk_endian_read_big32(data+12) == 0xccddeeff);

    SILK_ASSERT(silk_endian_read_big64(data) == 0x0011223344556677UL);
    SILK_ASSERT(silk_endian_read_big64(data+1) == 0x1122334455667788UL);
    SILK_ASSERT(silk_endian_read_big64(data+2) == 0x2233445566778899UL);
    SILK_ASSERT(silk_endian_read_big64(data+3) == 0x33445566778899aaUL);
    SILK_ASSERT(silk_endian_read_big64(data+4) == 0x445566778899aabbUL);
    SILK_ASSERT(silk_endian_read_big64(data+5) == 0x5566778899aabbccUL);
    SILK_ASSERT(silk_endian_read_big64(data+6) == 0x66778899aabbccddUL);
    SILK_ASSERT(silk_endian_read_big64(data+7) == 0x778899aabbccddeeUL);
    SILK_ASSERT(silk_endian_read_big64(data+8) == 0x8899aabbccddeeffUL);
}

void test_endian_write_little()
{
    uint8_t data[16];

    uint16_t test16[] = {0x0123, 0x4567, 0x89ab, 0xcbef};
    for (int i = 0; i < 4; i++)
    {
        silk_endian_write_little16(data, test16[i]);
        SILK_ASSERT(silk_endian_read_little16(data) == test16[i]);
    }

    uint32_t test32[] = {0x01230123, 0x45674567, 0x89ab89ab, 0xcbefcdef};
    for (int i = 0; i < 4; i++)
    {
        silk_endian_write_little32(data, test32[i]);
        SILK_ASSERT(silk_endian_read_little32(data) == test32[i]);
    }

    uint64_t test64[] = {
        0x0123012301230123UL, 
        0x4567456745674567UL, 
        0x89ab89ab89ab89abUL, 
        0xcbefcdefcdefcdefUL
    };
    for (int i = 0; i < 4; i++)
    {
        silk_endian_write_little64(data, test64[i]);
        SILK_ASSERT(silk_endian_read_little64(data) == test64[i]);
    }
}

void test_endian_write_big()
{
    uint8_t data[16];

    uint16_t test16[] = {0x0123, 0x4567, 0x89ab, 0xcbef};
    for (int i = 0; i < 4; i++)
    {
        silk_endian_write_big16(data, test16[i]);
        SILK_ASSERT(silk_endian_read_big16(data) == test16[i]);
    }

    uint32_t test32[] = {0x01230123, 0x45674567, 0x89ab89ab, 0xcbefcdef};
    for (int i = 0; i < 4; i++)
    {
        silk_endian_write_big32(data, test32[i]);
        SILK_ASSERT(silk_endian_read_big32(data) == test32[i]);
    }

    uint64_t test64[] = {
        0x0123012301230123UL, 
        0x4567456745674567UL, 
        0x89ab89ab89ab89abUL, 
        0xcbefcdefcdefcdefUL
    };
    for (int i = 0; i < 4; i++)
    {
        silk_endian_write_big64(data, test64[i]);
        SILK_ASSERT(silk_endian_read_big64(data) == test64[i]);
    }
}

void test_endian()
{
    test_endian_read_little();
    test_endian_read_big();
    test_endian_write_little();
    test_endian_write_big();
}