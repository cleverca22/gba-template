{
  outputs = { self, nixpkgs }:
  let
    pkgs = import nixpkgs { system = "x86_64-linux"; };
  in
  {
    packages.x86_64-linux.default = pkgs.pkgsCross.arm-embedded.callPackage ./src {};
    packages.x86_64-linux.test-script = pkgs.writeShellScriptBin "test-script" ''
      #cat ${self.packages.x86_64-linux.default}/flash.dis
      set -x
      ${pkgs.mgba}/bin/mgba -3 ${self.packages.x86_64-linux.default}/flash.elf --log-level=127 "$@"
    '';
  };
}
