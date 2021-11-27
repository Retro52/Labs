from PIL import Image, ImageDraw

HEIGHT = 540
WIDTH = 960

fname = "DS6.txt"


def drawDots(bg="black"):
    Ds6_image = Image.new("RGB", (WIDTH, HEIGHT), bg)
    draw = ImageDraw.Draw(Ds6_image)
    InputStream = open(fname, "r")
    if InputStream is None:
        print("Error occurred while opening dataset")
        exit(-1)
    coords = InputStream.readline()
    while coords is not None:
        try:
            coords = coords.split(" ")
            if len(coords) < 1 or coords[0] is None or coords[1] is None:
                break
            draw.point((int(coords[1]), HEIGHT - int(coords[0])))
            coords = InputStream.readline()
        except IndexError:
            break

    return Ds6_image


if __name__ == '__main__':
    img = drawDots()
    img.save("DS6.png")
