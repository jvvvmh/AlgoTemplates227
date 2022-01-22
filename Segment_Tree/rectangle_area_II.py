class Node:
    def __init__(self, st, ed, x):
        self.st = st       # idx
        self.ed = ed
        self.mid = (st + ed) // 2
        self.x = x         
        self.cover_len = 0 # 覆盖的真实长度
        self.cover_cnt = 0 # 可能被完整覆盖2次...
        self._lc = None # children
        self._rc = None
        
    @property
    def lc(self):
        self._lc = self._lc or Node(self.st, self.mid, self.x)
        return self._lc
    
    @property
    def rc(self):
        self._rc = self._rc or Node(self.mid, self.ed, self.x)
        return self._rc

    def update(self, cover_type, x1, x2):
        if (self.st == x1 and self.ed == x2 and (self.cover_cnt or self.st == self.ed-1)):
            self.cover_cnt += cover_type
            self.cover_len = 0 if self.cover_cnt <= 0 else self.x[x2] - self.x[x1]
            return self.cover_len
        # 优化!
            
        if x1 == x2:
            return self.cover_len

        mid = self.mid

        if self.cover_cnt > 0:
            self.lc.update(self.cover_cnt, self.st, mid)
            self.rc.update(self.cover_cnt, mid, self.ed)
        
        l1 = self.lc.update(cover_type, min(x1, mid), min(x2, mid))
        l2 = self.rc.update(cover_type, max(x1, mid), max(x2, mid))
        self.cover_len = l1 + l2
        self.cover_cnt = 0
        return self.cover_len
        

class Solution:
    def rectangleArea(self, rectangles: List[List[int]]) -> int:
        # nums: 左下 x1, y1, 右上 x2, y2
        # set(x_i) 排序 -> list x
        # 线段树记录 (1) 覆盖的真实长度 cover_len(2) 完整覆盖的次数 0,1,2,...
        # y_last, y_now, 更新res += dy * 覆盖的总长度
        x = set()
        e = []
        for x1, y1, x2, y2 in rectangles:
            if x1 < x2 and y1 < y2:
                e.append((y1, 1, x1, x2))
                e.append((y2, -1, x1, x2))
                x.add(x1)
                x.add(x2)
        x = sorted(x)
        idx = {}
        for i, v in enumerate(x):
            idx[v] = i
        e = sorted(e, key=lambda x: x[0])
        y_last = e[0][0]
        cover_len_last = 0
        res = 0
        node = Node(0, len(x) - 1, x)
        for y_now, in_out, x1, x2 in e:
            #print(y_now, in_out, idx[x1], idx[x2])
            res += (y_now - y_last) * cover_len_last
            # res %= int(1e9 + 7)
            # res %= (10**9 + 7)
            cover_len_last = node.update(in_out, idx[x1], idx[x2])
            # print(cover_len_last)
            y_last = y_now
        return  res % (10**9 + 7)