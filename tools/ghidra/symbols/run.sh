cargo build --release && \
./target/release/symbols \
  --overlay ../../../src/saturn/zero.c     ../../../build/saturn/zero.map \
  --overlay ../../../src/saturn/game.c     ../../../build/saturn/game.map \
  --overlay ../../../src/saturn/t_bat.c    ../../../build/saturn/t_bat.map \
  --overlay ../../../src/saturn/stage_02.c ../../../build/saturn/stage_02.map \
  --symbols_out_path ../out/symbols.json
