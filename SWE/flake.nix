{
  description = "JavaFX NixShell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { nixpkgs, ... }: {
    devShells.x86_64-linux =
      let pkgs = nixpkgs.legacyPackages.x86_64-linux;
      in {
        default = pkgs.mkShell {
          name = "java";
          buildInputs = with pkgs; [
            ant
            jdk17
            openjfx17
            glib
          ];

          shellHook = ''
            export PATH="$PATH:${pkgs.maven}/bin"
            export JAVA_HOME="${pkgs.jdk17}/lib/openjdk"
            export PATH="$PATH:$JAVA_HOME/bin"
            export LD_LIBRARY_PATH="${pkgs.libGL}/lib:${pkgs.gtk3}/lib:${pkgs.glib.out}/lib:${pkgs.xorg.libXtst}/lib:$LD_LIBRARY_PATH"   
            export JAVAFX_PATH="${pkgs.openjfx17}/lib"
          '';
        };
      };
  };
}
