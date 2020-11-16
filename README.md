# DD Image

DD Image is a python script for search and delete duplicate images.

## Supported formats:

* [jpg]
* [png]
## Installation

If you don't have the following dependencies use the package manager [pip](https://pip.pypa.io/en/stable/) to install dependencies.

```bash
pip install opencv-python
pip install opencv-contrib-python
```
## Usage

Automatic Mode
```bash
python3 DDImage /path_to_folder_whit_images True
```
Manual Mode, when an image and the duplicate is showed on your screen, press esc for delete the copy or press any other key for do nothing
```bash
python3 DDImage /path_to_folder_whit_images
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
