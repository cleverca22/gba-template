{ stdenv, llvm }:

stdenv.mkDerivation {
  name = "foo";
  nativeBuildInputs = [ llvm ];
  src = ./.;
  NIX_DEBUG = false;
  hardeningDisable = [ "fortify" "stackprotector" "relro" "bindnow" ];
}
