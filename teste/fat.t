-- calcular fatorial de um inteiro
read x;
if x > 0 then
    fat := 1;
    while x > 0 do
        fat := fat * x;
        x := x - 1
    enddo
    write fat;
endif
