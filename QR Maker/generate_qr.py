# Just do this :: python3 generate_qr.py or you can just press ▶︎

import qrcode

def generate_qr_code(text, filename):
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
    )
    qr.add_data(text)
    qr.make(fit=True)
    img = qr.make_image(fill_color="#6aff9b", back_color="#292535")
    img.save(filename)

# Input the Url to Generate to generate the QR Code
# ---------------------------------------------------------------------------
text = "https://www.google.com"
# ___________________________________________________________________________

filename = "qrcode.png"             # Filename that the generated QR Code is saved as
generate_qr_code(text, filename)    # Generate the QR Code
print(f"\n✅ Successfully generated QR Code")
print(f"🎉 Filename: {filename}")

