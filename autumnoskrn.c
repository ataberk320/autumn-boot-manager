typedef struct {
    void* FramebufferBase;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelsPerScanLine;

} GraphicsOutputProtocolData;

void kernel_main(GraphicsOutputProtocolData* gopd) {
    unsigned int x, y;
    unsigned int* framebuffer = (unsigned int*)gopd->FramebufferBase;

    for (y = 0; y < gopd->Height; y++) {
        for (x = 0; x < gopd->Width; x++) {
            framebuffer[y * gopd->PixelsPerScanLine + x] = 0x00FF00FF;

        }

    }
    while (1);
}