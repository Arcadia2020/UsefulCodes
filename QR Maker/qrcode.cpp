/*
Steps:
> g++ -std=c++17 qrcode.cpp -o generate_qr -lqrencode -lpng
> ./generate_qr

| Part           | What it is    | What it does                                                                  |
|----------------|---------------|-------------------------------------------------------------------------------|
| g++            | The compiler  | Invokes the GNU C++ compiler                                                  |
| -std=c++17     | Standard flag | Tells the compiler to use the c++17 standard                                  |
| qrcode.cpp     | Source file   | Your input —— The C++ code you wrote                                          |
| -o generate_qr | Output flag   | Names the compiled binary 'generate_qr'. Without '-o', it defaults to 'a.out' |
| -lqrencode     | Library link  | Links the libqrencode library (`-l` + library name).                          |
| -lpng          | Library link  | Links the **libpng** library.                                                 |
*/


// ─── INCLUDES ───────────────────────────────────────────────────────────────
#include <iostream>     // cout, cerr  (console input/output)
#include <string>       // std::string (text handling)
#include <vector>       // std::vector (dynamic arrays)
#include <stdexcept>    // std::runtime_error (exception handling)
#include <qrencode.h>   // libqrencode  — generates QR code data (external library)
#include <png.h>        // libpng       — writes PNG image files (external library)
using namespace std;    // Lets us write string/vector/cout instead of std::string etc.


// ─── COLOR CONSTANTS ────────────────────────────────────────────────────────
// uint8_t = unsigned 8-bit integer → holds values 0–255, perfect for RGB channels
// [3]     = an array of exactly 3 values (Red, Green, Blue)
const uint8_t FILL_COLOR[3] = {0x6a, 0xff, 0x9b};   // #6aff9b
const uint8_t BACK_COLOR[3] = {0x29, 0x25, 0x35};   // #292535


// ─── FUNCTION SIGNATURE ─────────────────────────────────────────────────────
// text          => The URL or text to encode into the QR
// filename      => Where to save the output PNG file
// box_size = 10 => Each QR "module" (dot) = 10×10 pixels (default value)
// border = 4    => Quiet zone = 4 modules wide on every side (QR standard recommends ≥4)
void generate_qr_code(const string& text, const string& filename, int box_size = 10, int border = 4) {

    // ─── STEP 1: Generate QR binary data ────────────────────────────────────
    QRcode* qr = QRcode_encodeString(
        text.c_str(),       // .c_str() converts std::string → const char* (C-style string)
                            // because the C library function expects a raw char pointer

        1,                  // version (1 = auto-select
                            // libqrencode picks the smallest version that fits the data, version 1–40

        QR_ECLEVEL_L,       // Error Correction Level LOW → ~7% of data can be restored
                            // Other levels: M (15%), Q (25%), H (30%)

        QR_MODE_8,          // Encoding mode: 8-bit byte mode; Other modes: NUMERIC, ALPHANUMERIC, KANJI
                            // Handles the full ASCII/UTF-8 range (vs numeric-only, etc.)

        1                   // caseSensitive: 1 means true. So, 'A' and 'a' are treated differently
    );

    // If qr is a null pointer (encoding failed), throw an exception with a message
    if (!qr) throw runtime_error("Failed to generate QR code");

    // qr->width = number of modules (dots) per side of the QR grid
    int qr_size   = qr->width;
    // eg: A Ver2 QRcode is 25x25, so qr_size = 25

    // Total image pixel size calculation:
    int img_size  = (qr_size + border * 2) * box_size;
    // qr_size + border * 2 → add quiet zone on both sides (left + right, top + bottom)
    // *box_size            → scale up from modules to pixels
    // eg: (25+(4*2))*10 = (25+8)*10 = 33*10 = 330 pixels wide & tall


    // ─── STEP 2: Build a pixel color buffer ─────────────────────────────────
    vector<vector<array<uint8_t, 3>>> pixels( img_size, vector<array<uint8_t, 3>>(img_size) );
    // Declare a 2D grid of pixels, each pixel = array of 3 bytes [R, G, B]
    // vector<...>(img_size, ...) → outer vector: img_size rows
    // vector<array<uint8_t,3>>(img_size) → each row: img_size columns
    // So pixels[y][x] gives the RGB color at position (x, y)

    for (int y = 0; y < img_size; y++) {            // Loop over every pixel row
        for (int x = 0; x < img_size; x++) {        // Loop over every pixel in that row

            // Convert pixel x-coordinate → QR module column index
            int qx = x / box_size - border;
            // x / box_size → which box we're in (integer division)
            // - border     → shift left to account for the quiet zone offset

            // Same idea for the y (row) direction
            int qy = y / box_size - border;


            bool is_dark = (qx >= 0 && qx < qr_size &&          // qx is within the QR grid
                            qy >= 0 && qy < qr_size &&          // qy is within the QR grid
                            (qr->data[qy * qr_size + qx] & 1)); // qr->data is a flat 1D byte array of the QR modules
                                                                // Index: qy * qr_size + qx converts 2D (col, row) → 1D position
                                                                // & 1 → bitwise AND: checks if the lowest bit is 1 (dark) or 0 (light)
                                                                // The entire expression is false if (qx,qy) is in the border (quiet zone)

            pixels[y][x] = is_dark ? array<uint8_t,3>{FILL_COLOR[0], FILL_COLOR[1], FILL_COLOR[2]} : array<uint8_t,3>{BACK_COLOR[0], BACK_COLOR[1], BACK_COLOR[2]};
            // Ternary operator: if dark → use fill color (green), else → background (purple)
            // array<uint8_t,3>{R, G, B} → construct a fixed 3-element array inline
        }
    }


    QRcode_free(qr);


    // ── STEP 3: Write the pixel buffer to a PNG file ─────────────────────────
    FILE* fp = fopen(filename.c_str(), "wb");                       // Returns a FILE* pointer, or nullptr if the file couldn't be opened
    if (!fp) throw runtime_error("Cannot open file for writing");   // Guard: if fopen() failed (bad path, no permissions), throw and stop

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    // png_structp              → libpng's main control structure (holds all PNG write state)
    // PNG_LIBPNG_VER_STRING    → version string — libpng checks this to ensure ABI compatibility
    // The three nullptr args   → custom error handler, error data, warning handler (we use defaults)

    png_infop   info = png_create_info_struct(png);
    // png_infop → a secondary structure that holds image metadata (dimensions, color type, etc). Must be created separately from the main write struct

    png_init_io(png, fp);
    // Tells libpng to write PNG data into our FILE* (fp)
    // This connects the library's internal write callbacks to the file handle

    png_set_IHDR(png, info,
                 img_size,                    // Image width in pixels
                 img_size,                    // Image height in pixels
                 8,                           // Bit depth: 8 bits per channel (0–255 per R/G/B)
                 PNG_COLOR_TYPE_RGB,          // Color type: 3 channels (R, G, B), no alpha
                 PNG_INTERLACE_NONE,          // No interlacing (progressive load) — simpler format
                 PNG_COMPRESSION_TYPE_DEFAULT,// Standard zlib compression
                 PNG_FILTER_TYPE_DEFAULT);    // Standard PNG row filtering (improves compression)
                                              // IHDR = "Image HeaDer" — the first required chunk in every PNG file

    png_write_info(png, info);
    // Flushes the header metadata (IHDR chunk and others) to the file
    // Must be called before writing any pixel rows

    vector<uint8_t> row(img_size * 3);
    // Allocate a temporary 1D buffer for one row of pixels
    // Each pixel = 3 bytes (R, G, B), so row size = img_size * 3 bytes

    for (int y = 0; y < img_size; y++) {        // Iterate over each pixel row top-to-bottom
        for (int x = 0; x < img_size; x++) {    // Pack each pixel's RGB into the flat row buffer
            row[x * 3 + 0] = pixels[y][x][0];   // Red channel   of pixel at column x
            row[x * 3 + 1] = pixels[y][x][1];   // Green channel of pixel at column x
            row[x * 3 + 2] = pixels[y][x][2];   // Blue channel  of pixel at column x
            
            // x * 3 → each pixel occupies 3 consecutive bytes in the flat array
        }

        png_write_row(png, row.data());
        // row.data() → raw pointer to the underlying array of the vector
        // Writes this one row of RGB bytes into the PNG file (libpng handles compression)
    }

    // Writes the PNG end-of-file marker (IEND chunk)
    // nullptr → no need to write additional metadata after pixel data
    png_write_end(png, nullptr);
    
    // Frees all memory libpng allocated for the png and info structs
    // Takes pointers-to-pointers so it can also null out the pointers afterward
    png_destroy_write_struct(&png, &info);

    // Close the file handle — flushes any OS-level write buffers and releases the file
    fclose(fp);
}


// ─── MAIN ENTRY POINT ───────────────────────────────────────────────────────
int main() {
    // ————————————————————————————————————————————————————————————————————————
    string text = "https://claude.ai/chat/82968b72-91f4-4d62-9253-36336053706f";
    // ________________________________________________________________________

    string filename = "qrcode.png";     // The output file name — will be created in the same directory as the binary

    try {
        generate_qr_code(text, filename);       // Call the function — uses default box_size=10 and border=4
                                                // If anything goes wrong inside, it throws a runtime_error

        cout << "\n✅ Successfully generated QR Code\n";
        cout << "🎉 Filename: " << filename << "\n";

    } catch (const exception& e) {
        // Catches any exception that inherits from std::exception
        // (runtime_error does, which is what we throw above)

        cerr << "❌ Error: " << e.what() << "\n";
        // e.what() → returns the error message string we passed to runtime_error()
        // cerr     → writes to stderr (separate stream from cout, better for errors)

        return 1;
        // Return 1 to the OS → signals that the program exited with an error
        // Convention: 0 = success, non-zero = failure
    }

    return 0;   // Return 0 → signals successful execution to the OS / calling shell
}
