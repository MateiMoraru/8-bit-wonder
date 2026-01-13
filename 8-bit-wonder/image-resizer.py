import sys
from PIL import Image

def resize_pixelart(input_path, output_path, new_width=16, new_height=16):
    try:
        # Open image
        img = Image.open(input_path)

        # Resize with nearest-neighbor (preserves pixel art)
        resized_img = img.resize((new_width, new_height), resample=Image.NEAREST)

        # Save output
        resized_img.save(output_path)
        print(f"Saved resized image to '{output_path}' ({new_width}x{new_height})")

    except Exception as e:
        print(f"Error: {e}")

def main():
    if len(sys.argv) != 3:
        print("Usage: python3 image-resizer.py <input_image> <output_image>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]

    resize_pixelart(input_path, output_path)

if __name__ == "__main__":
    main()