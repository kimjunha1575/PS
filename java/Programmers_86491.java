class Programmers_86491 {

  public int solution(int[][] sizes) {
    int maxW = 0;
    int maxH = 0;
    for (int[] size : sizes) {
      int w = size[0];
      int h = size[1];
      if (w < h) {
        int temp = w;
        w = h;
        h = temp;
      }
      if (w > maxW) {
        maxW = w;
      }
      if (h > maxH) {
        maxH = h;
      }
    }
    return maxW * maxH;
  }
}
