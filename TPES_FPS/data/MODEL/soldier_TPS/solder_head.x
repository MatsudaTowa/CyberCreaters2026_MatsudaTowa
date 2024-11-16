xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 46;
 0.02745;25.78100;0.00000;,
 6.57286;21.94681;-6.54542;,
 0.02745;21.94681;-9.25662;,
 9.28406;21.94681;0.00000;,
 6.57286;21.94681;6.54542;,
 0.02745;21.94681;9.25662;,
 -6.51797;21.94681;6.54542;,
 -9.22917;21.94681;-0.00000;,
 -6.51797;21.94681;-6.54542;,
 9.28406;12.69018;-9.25662;,
 0.02745;12.69018;-13.09084;,
 13.11828;12.69018;0.00000;,
 9.28406;12.69018;9.25662;,
 0.02745;12.69018;13.09084;,
 -9.22917;12.69018;9.25662;,
 -13.06337;12.69018;-0.00000;,
 -9.22917;12.69018;-9.25662;,
 6.57286;3.43356;-6.54542;,
 0.02745;3.43356;-9.25662;,
 9.28406;3.43356;0.00000;,
 6.57286;3.43356;6.54542;,
 0.02745;3.43356;9.25662;,
 -6.51797;3.43356;6.54542;,
 -9.22917;3.43356;-0.00000;,
 -6.51797;3.43356;-6.54542;,
 0.02745;-0.40066;-0.00000;,
 0.00738;31.50667;0.00000;,
 8.35017;27.51637;-4.81671;,
 0.00738;27.51637;-9.63343;,
 8.35017;27.51637;4.81671;,
 0.00738;27.51637;9.63343;,
 -8.33542;27.51637;4.81671;,
 -8.33542;27.51637;-4.81671;,
 11.80587;17.88293;-6.81186;,
 0.00738;17.88293;-13.62372;,
 11.80586;17.88293;6.81186;,
 0.00738;17.88293;13.62372;,
 -11.79111;17.88293;6.81186;,
 -11.79111;17.88293;-6.81186;,
 8.35017;22.23083;-4.81671;,
 0.00738;22.23083;-9.63343;,
 8.35017;22.23083;4.81671;,
 0.00738;22.23083;9.63343;,
 -8.33542;22.23083;4.81671;,
 -8.33542;22.23083;-4.81671;,
 0.00738;18.24050;0.00000;;
 
 56;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 3;18,17,25;,
 3;17,19,25;,
 3;19,20,25;,
 3;20,21,25;,
 3;21,22,25;,
 3;22,23,25;,
 3;23,24,25;,
 3;24,18,25;,
 3;26,27,28;,
 3;26,29,27;,
 3;26,30,29;,
 3;26,31,30;,
 3;26,32,31;,
 3;26,28,32;,
 4;28,27,33,34;,
 4;27,29,35,33;,
 4;29,30,36,35;,
 4;30,31,37,36;,
 4;31,32,38,37;,
 4;32,28,34,38;,
 4;34,33,39,40;,
 4;33,35,41,39;,
 4;35,36,42,41;,
 4;36,37,43,42;,
 4;37,38,44,43;,
 4;38,34,40,44;,
 3;40,39,45;,
 3;39,41,45;,
 3;41,42,45;,
 3;42,43,45;,
 3;43,44,45;,
 3;44,40,45;;
 
 MeshMaterialList {
  3;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.530196;0.395294;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.175686;0.241569;0.125490;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  52;
  0.000000;1.000000;0.000000;,
  -0.000000;0.715248;-0.698871;,
  0.494177;0.715248;-0.494176;,
  0.698871;0.715247;0.000000;,
  0.494177;0.715248;0.494176;,
  -0.000000;0.715248;0.698871;,
  -0.494177;0.715247;0.494176;,
  -0.698871;0.715247;-0.000000;,
  -0.494177;0.715247;-0.494176;,
  0.000000;-0.000000;-1.000000;,
  0.707107;-0.000000;-0.707107;,
  1.000000;-0.000000;0.000000;,
  0.707107;-0.000000;0.707107;,
  -0.000000;-0.000000;1.000000;,
  -0.707107;-0.000000;0.707106;,
  -1.000000;-0.000000;-0.000000;,
  -0.707107;-0.000000;-0.707106;,
  -0.000000;-0.715247;-0.698872;,
  0.494177;-0.715246;-0.494177;,
  0.698872;-0.715246;0.000000;,
  0.494177;-0.715246;0.494177;,
  -0.000000;-0.715247;0.698872;,
  -0.494177;-0.715246;0.494177;,
  -0.698872;-0.715246;0.000000;,
  -0.494177;-0.715246;-0.494177;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.721779;-0.692124;,
  0.599397;0.721779;-0.346062;,
  0.599397;0.721779;0.346062;,
  0.000000;0.721779;0.692124;,
  -0.599397;0.721779;0.346062;,
  -0.599397;0.721779;-0.346062;,
  0.000000;0.382683;-0.923880;,
  0.800103;0.382683;-0.461940;,
  0.800103;0.382683;0.461940;,
  0.000000;0.382683;0.923880;,
  -0.800103;0.382683;0.461940;,
  -0.800103;0.382682;-0.461940;,
  0.000000;-0.676159;0.736756;,
  -0.638049;-0.676159;0.368378;,
  -0.638049;-0.676159;-0.368378;,
  0.000000;-0.676159;-0.736756;,
  0.638050;-0.676159;-0.368378;,
  0.638050;-0.676159;0.368378;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.923878;-0.382686;,
  0.331416;-0.923878;-0.191343;,
  0.331416;-0.923878;0.191343;,
  0.000000;-0.923878;0.382686;,
  -0.331416;-0.923878;0.191343;,
  -0.331416;-0.923878;-0.191343;;
  56;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  3;17,18,25;,
  3;18,19,25;,
  3;19,20,25;,
  3;20,21,25;,
  3;21,22,25;,
  3;22,23,25;,
  3;23,24,25;,
  3;24,17,25;,
  3;26,28,27;,
  3;26,29,28;,
  3;26,30,29;,
  3;26,31,30;,
  3;26,32,31;,
  3;26,27,32;,
  4;27,28,34,33;,
  4;28,29,35,34;,
  4;29,30,36,35;,
  4;30,31,37,36;,
  4;31,32,38,37;,
  4;32,27,33,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,39,39,44;,
  3;46,47,45;,
  3;47,48,45;,
  3;48,49,45;,
  3;49,50,45;,
  3;50,51,45;,
  3;51,46,45;;
 }
}
