import const_ref_self

print("--- Start ---")
print("--- Environ ---")
s = const_ref_self.singleton()
print(s.get())

print("--- Constructible ---")
c = const_ref_self.Constructible()
print(c.get())

print("--- End ---")
