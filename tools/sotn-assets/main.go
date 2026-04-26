package main

import (
	"context"
	"fmt"
	"os"
	"slices"

	"github.com/spf13/cobra"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/format"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/mods"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
)

var acceptedVersions = []string{"us", "hd", "pspeu"}

func getVersionFromArgs(args []string) (string, bool, error) {
	firstArgIsVersion := false
	version := os.Getenv("VERSION")
	if len(args) > 0 && slices.Contains(acceptedVersions, args[0]) {
		version = args[0]
		firstArgIsVersion = true
	}
	if version == "" {
		_, _ = fmt.Fprintln(os.Stderr, "WARNING: no version specified, assume 'us'")
		version = "us"
	}
	if !slices.Contains(acceptedVersions, version) {
		return "", firstArgIsVersion, fmt.Errorf("version %s invalid; valid values are: %v\n", version, acceptedVersions)
	}
	return version, firstArgIsVersion, nil
}

func main() {
	rootCmd := &cobra.Command{
		Short:         "SOTN assets, build, and tooling orchestrator",
		Long:          "Wraps all the build-chain and tooling with a clear and simple interface",
		SilenceErrors: true,
	}
	rootCmd.AddCommand(&cobra.Command{
		Use:          "build [version...]",
		Short:        "Build game files (downloads dependencies automatically)",
		Long:         "Build one or more game versions. If no version is specified, builds all versions (us, hd, pspeu).",
		SilenceUsage: true,
		RunE: func(cmd *cobra.Command, args []string) error {
			versions, err := parseBuildArgs(args)
			if err != nil {
				return err
			}
			return buildVersions(versions)
		},
	})
	checkCmd := &cobra.Command{
		Use:          "check [version|all]",
		Short:        "Check for matching checksums for all imported files",
		SilenceUsage: true,
		RunE: func(cmd *cobra.Command, args []string) error {
			versions, err := parseBuildArgs(args)
			if err != nil {
				return err
			}
			return checkVersions(os.Stderr, versions)
		},
	}
	rootCmd.AddCommand(checkCmd)
	cleanCmd := &cobra.Command{
		Use:          "clean [version|all]",
		Short:        "Clean extracted files, assets, and build artifacts for a version (or all versions)",
		SilenceUsage: true,
		RunE: func(cmd *cobra.Command, args []string) error {
			verbose, _ := cmd.Flags().GetBool("verbose")
			version := ""
			if len(args) > 0 {
				version = args[0]
			}
			return clean(version, verbose)
		},
	}
	cleanCmd.Flags().BoolP("verbose", "v", false, "Echo git clean stdout and stderr")
	rootCmd.AddCommand(cleanCmd)
	rootCmd.AddCommand(&cobra.Command{
		Use:          "extract-saturn",
		Short:        "Extract Saturn asm stubs from disc files using saturn-splitter",
		SilenceUsage: true,
		RunE: func(cmd *cobra.Command, args []string) error {
			if err := deps.EnsureBuildDeps([]string{"saturn"}); err != nil {
				return err
			}
			return runSaturnSplitter()
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "extract-assets <asset.yaml>",
		Short:        "Extract asset files from the disk files",
		SilenceUsage: true,
		Args:         cobra.ExactArgs(1),
		RunE: func(cmd *cobra.Command, args []string) error {
			c, err := readConfig(args[0])
			if err != nil {
				return err
			}
			if c.Version != "" {
				_ = os.Setenv("VERSION", string(c.Version))
			}
			return extractFromConfig(c)
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "build-assets <asset.yaml>",
		Short:        "Build asset files from the extracted assets",
		SilenceUsage: true,
		Args:         cobra.ExactArgs(1),
		RunE: func(cmd *cobra.Command, args []string) error {
			c, err := readConfig(args[0])
			if err != nil {
				return err
			}
			if c.Version != "" {
				_ = os.Setenv("VERSION", string(c.Version))
			}
			return buildFromConfig(c)
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "format",
		Short:        "Format code base",
		SilenceUsage: true,
		RunE: func(cmd *cobra.Command, args []string) error {
			return format.Format()
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "info <stage_ovl.bin>",
		Short:        "Attempt to parse and print the asset configuration for a given stage overlay",
		SilenceUsage: true,
		Args:         cobra.ExactArgs(1),
		RunE: func(cmd *cobra.Command, args []string) error {
			return info(os.Stdout, args[0])
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "objdiff-gen [version]",
		Short:        "Generate an updated objdiff.json for the specified game version",
		SilenceUsage: true,
		Args: func(cmd *cobra.Command, args []string) error {
			version, _, err := getVersionFromArgs(args)
			if err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "version", version))
			return nil
		},
		RunE: func(cmd *cobra.Command, args []string) error {
			version := cmd.Context().Value("version").(string)
			c, err := readConfigVersion(version)
			if err != nil {
				return err
			}
			return objdiffgen(c, false)
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "objdiff-gui [version]",
		Short:        "Invoke objdiff-gui to diff decompiled code locally",
		SilenceUsage: true,
		Args: func(cmd *cobra.Command, args []string) error {
			version, _, err := getVersionFromArgs(args)
			if err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "version", version))
			return nil
		},
		RunE: func(cmd *cobra.Command, args []string) error {
			version := cmd.Context().Value("version").(string)
			return handleObjdiffGUI(version)
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "objdiff [version] c_path func_name",
		Short:        "Invoke objdiff to diff decompiled code locally from your terminal",
		SilenceUsage: true,
		Args: func(cmd *cobra.Command, args []string) error {
			version, firstArgIsVersion, err := getVersionFromArgs(args)
			if err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "version", version))
			exactArgs := 2
			if firstArgIsVersion {
				exactArgs = 3
			}
			if err := cobra.ExactArgs(exactArgs)(cmd, args); err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "src_path", args[exactArgs-2]))
			cmd.SetContext(context.WithValue(cmd.Context(), "func_name", args[exactArgs-1]))
			return nil
		},
		Example: "   objdiff us dra/4A538 func_800EAD0C",
		RunE: func(cmd *cobra.Command, args []string) error {
			version := cmd.Context().Value("version").(string)
			srcPath := cmd.Context().Value("src_path").(string)
			funcName := cmd.Context().Value("func_name").(string)
			return handlerObjdiffCLI(version, srcPath, funcName)
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "bindiff [version] overlay",
		Short:        "Invoke gobindiff to visualize binary differences between the bult and the target overlay",
		SilenceUsage: true,
		Args: func(cmd *cobra.Command, args []string) error {
			version, firstArgIsVersion, err := getVersionFromArgs(args)
			if err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "version", version))
			exactArgs := 1
			if firstArgIsVersion {
				exactArgs = 2
			}
			if err := cobra.ExactArgs(exactArgs)(cmd, args); err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "overlay", args[exactArgs-1]))
			return nil
		},
		Example: "   bindiff pspeu dai",
		RunE: func(cmd *cobra.Command, args []string) error {
			version := cmd.Context().Value("version").(string)
			ovl := cmd.Context().Value("overlay").(string)
			return handleBindiff(version, ovl, 24)
		},
	})
	rootCmd.AddCommand(&cobra.Command{
		Use:          "progress [version]",
		Short:        "Generate a progress report for https://decomp.dev/Xeeynamo/sotn-decomp",
		SilenceUsage: true,
		Args: func(cmd *cobra.Command, args []string) error {
			version, _, err := getVersionFromArgs(args)
			if err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "version", version))
			return nil
		},
		RunE: func(cmd *cobra.Command, args []string) error {
			version := cmd.Context().Value("version").(string)
			return handleObjdiffReport(version)
		},
	})
	diskCmd := &cobra.Command{
		Use:          "disk",
		Short:        "Generate a PlayStation 1 disk image from build/us",
		SilenceUsage: true,
		Args: func(cmd *cobra.Command, args []string) error {
			version, _, err := getVersionFromArgs(args)
			if err != nil {
				return err
			}
			cmd.SetContext(context.WithValue(cmd.Context(), "version", version))
			return nil
		},
		RunE: func(cmd *cobra.Command, args []string) error {
			version := cmd.Context().Value("version").(string)
			if sotn.Version(version) != sotn.VersionUS {
				_, _ = fmt.Fprintf(os.Stderr, "SOTN version %s not supported\n", sotn.Version(version))
				return nil
			}
			lbaDryRun, _ := cmd.Flags().GetBool("lba-dry-run")
			err := mods.MakeDisk("build/sotn.us.cue", "build/us", "disks/us", "config/disk.us.lba", lbaDryRun)
			if err != nil {
				_, _ = fmt.Fprintf(os.Stderr, "generate modded disk: %s\n", err)
			}
			return err
		},
	}
	diskCmd.Flags().Bool("lba-dry-run", false, "Compute disk layout and print include/lba.h to stdout")
	rootCmd.AddCommand(diskCmd)
	if err := rootCmd.Execute(); err != nil {
		_, _ = fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
}
