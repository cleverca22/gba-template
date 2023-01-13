{ stdenv, llvm, util-linux }:

stdenv.mkDerivation {
  name = "foo";
  nativeBuildInputs = [ llvm util-linux ];
  src = ./.;
  NIX_DEBUG = false;
  hardeningDisable = [ "fortify" "stackprotector" "relro" "bindnow" ];
}
