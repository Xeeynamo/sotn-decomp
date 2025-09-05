// SPDX-License-Identifier: AGPL-3.0-or-later

// The clocktower defines two types of drawing "scripts" - the first for
// the pyramid roof sections and the second for quad clock faces and
// tower. These have slightly different structure, but work the same
// way. An `SVECTOR` array is chosen from an array of pointers
// (`s_ClockVertexSets`) using the special value `0x80`. The next value
// will be used to choose the vector array that subsequent vertexes will
// be chosen from. After the vertex array selection, one or more polygon
// definitions follows. These polygons are always of the same type
// and have the same size.
//
// Each entry consits of a `textureIndex`, followed by the vertexes
// necessary to build the polygon. After the vertexes comes a priority
// which is added to a constant value.
//
// A value of 0xFF is used to denote the end of the script.

// declares which vertex array will be used for subsequent polygons
#define VINDEX_MARKER 0x80
#define VINDEX(i) VINDEX_MARKER, (i)

// indicates the end of the drawing script
#define OBJ_END 0xFF

// Sets up a triangle for drawing. `textureIndex` is
// an index into a texture lookup table. Each vertex is an
// index into the table defined by the previous `VINDEX`
// declaration. `priority` is the `Primitive` priority
// plus a constant defined by the consumer.
#define DRAW_TRIANGLE(textureIndex, v1, v2, v3, priority)                      \
    (textureIndex), (v1), (v2), (v3), (priority)

// Quads are defined by declaring vertexes in the
// order top-left, top-right, bottom-left, bottom-right.
// Often the sets list the quads in clockwise order, so
// the `QUAD` macro reflects the difference in expected
// order.
#define DRAW_QUAD(textureIndex, v1, v2, v4, v3, priority)                      \
    (textureIndex), (v1), (v2), (v4), (v3), (priority)
