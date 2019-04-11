from PIL import ImageEnhance, Image
import io
import sfs

DEFAULT_FILTERS = [
    (ImageEnhance.Color, 0.0),
    (ImageEnhance.Contrast, 1.5),
    (ImageEnhance.Sharpness, 2.0),
]


def process_image(input_file, output_file, filters, local):
    """Apply series of filters to input_file and record changes in output_file."""
    if local:
        image = Image.open(input_file)
    else:
        image_file = sfs.open(input_file, "rb")
        image = Image.open(image_file)

    for enhancer, factor in filters:
        image = enhancer(image).enhance(factor)
    image.save(output_file, "JPEG")


def process_imamges(input_files, output_files, filters, local):
    """Apply filters to multiple files."""
    for i, input_file in enumerate(input_files):
        process_image(input_file, output_files[i], filters, local)


def process_image_arguments(input_folder, output_folder, filters, local, files):
    """Generator to process process_image arguments into a tuple."""
    for file_name in files:
        input_file = "{}/{}".format(input_folder, file_name)
        output_file = "{}/{}".format(output_folder, file_name)
        yield (input_file, output_file, filters, local)

if __name__ == "__main__":
    import os
    mount_point = os.environ["NFS4_SERVER"]
    sfs.mount(mount_point)
    sfs_file = sfs.open("/cat.jpg", "rb")
    reg_file = open("/efs/cat.jpg", "rb")
    sfs_data = sfs_file.read()
    reg_data = reg_file.read()
    print(len(sfs_data))
    print(len(reg_data))


