{
  description = "openGl NixShell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { nixpkgs, ... }: {
    devShells.x86_64-linux =
      let
        pkgs = nixpkgs.legacyPackages.x86_64-linux;
      in
      {
        default = pkgs.mkShell {
          name = "openGl";
          buildInputs = with pkgs; [
            cmake
            gcc
            wxGTK32
            libGL
            libGLU
            mesa
            freeglut
            glfw
            glew
          ];
        };
      };
  };
}
