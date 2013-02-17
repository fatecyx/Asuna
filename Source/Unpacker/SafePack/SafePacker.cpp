#include "SafePacker.h"

HRESULT EncryptScript(PVOID pvBuffer, ULONG BufferSize, ULONG Version)
{
    PBYTE pbFile, pbBuffer;
    ULONG Mask, Part1, Part2;

    UNREFERENCED_PARAMETER(BufferSize);

    if (*(PULONG)pvBuffer != TAG4('YSTB'))
        return TYPE_E_UNSUPFORMAT;

    pbFile = (PBYTE)pvBuffer;
    pbBuffer = pbFile + 0x20;

    switch (Version)
    {
        case 0x107:
            Mask = TAG4(0x07B4024A);
            Mask = 0x4A02B407;
            Part1 = *(PULong)(pbFile + 0x8);
            Part2 = *(PULong)(pbFile + 0xC);
            break;

        case 0x122:
        case 0x1C2:
        case 0x1F4:
            Part1 = *(PULong)(pbFile + 0xC);
            Part2 = *(PULong)(pbFile + 0x10);
            Mask = 0x96AC6FD3;
            break;

        default:
            return TYPE_E_UNSUPFORMAT;
    }

    while (Part1 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part1 -= 4;
    }
    for (ULONG i = 0, j = Part1; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    while (Part2 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part2 -= 4;
    }
    for (ULONG i = 0, j = Part2; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    if (Version == 0x107)
        return S_OK;

    Part1 = *(PULong)(pbFile + 0x14);
    Part2 = *(PULong)(pbFile + 0x18);

    while (Part1 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part1 -= 4;
    }
    for (ULONG i = 0, j = Part1; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    while (Part2 > 3)
    {
        *(PULong)pbBuffer ^= Mask;
        pbBuffer += 4;
        Part2 -= 4;
    }
    for (ULONG i = 0, j = Part2; i != j; ++i)
        *pbBuffer++ ^= Mask >> (i * 8);

    return S_OK;
}