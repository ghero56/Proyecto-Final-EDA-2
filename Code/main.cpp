#include "funciones.cpp"

/* ---------- Funcion main --------- */
int main(int argc, char const *argv[])
{
  if(strcmp(argv[1],"admin") == 0) admin();

  else regular();

  return 0;
}
