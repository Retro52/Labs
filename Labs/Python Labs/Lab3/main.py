from PIL import Image, ImageDraw

HEIGHT = 540
WIDTH = 960

fname = "DS6.txt"


def Left_index(pts):
    minn = 0
    for i in range(1, len(pts)):
        if pts[i][0] < pts[minn][0]:
            minn = i
        elif pts[i][0] == pts[minn][0]:
            if pts[i][1] > pts[minn][1]:
                minn = i
    return minn


def orientation(p, q, r):
    val = (q[1] - p[1]) * (r[0] - q[0]) - \
          (q[0] - p[0]) * (r[1] - q[1])

    if val == 0:
        return 0  # colinear
    elif val > 0:
        return 1  # clockwise
    else:
        return 2  # not clockwise


def convexHull(pts, n):
    leftIndex = Left_index(pts)

    hull = []

    p = leftIndex
    while True:
        hull.append(p)

        q = (p + 1) % n

        for i in range(n):

            # If i is more counterclockwise than current q, update q
            if orientation(pts[p], pts[i], pts[q]) == 2:
                q = i
        p = q

        # While we don't come to first point
        if p == leftIndex:
            break

    result = []
    for each in hull:
        result.append([pts[each][0], pts[each][1]])
    return result


def getPoints():
    resultCoords = []
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
            resultCoords.append([int(coords[1]), HEIGHT - int(coords[0])])
            coords = InputStream.readline()
        except IndexError:
            break
    return resultCoords


def EditImage(pts, bg=(255, 255, 255, 1)):
    Ds6_image = Image.new("RGB", (WIDTH, HEIGHT), bg)
    draw = ImageDraw.Draw(Ds6_image)
    for i in range(len(pts)):
        if i == len(pts) - 1:
            draw.line(pts[i] + pts[0], fill=(0, 26, 191, 1))
        else:
            draw.line(pts[i] + pts[i + 1], fill=(0, 26, 191, 1))
    return Ds6_image


if __name__ == '__main__':
    points = getPoints()
    img = EditImage(convexHull(points, len(points)))
    # print(convexHull(points, len(points)))
    # print()
    img.save("Lab3.png")
