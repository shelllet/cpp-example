class Base:
    def ss(self):
        return 0

class __Base(Base):
    def ss(self):
        return 10






b = __Base()

print(b.ss())