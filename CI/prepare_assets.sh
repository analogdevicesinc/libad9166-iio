#!/bin/bash -e

release_artifacts() {
	cd "${BUILD_ARTIFACTSTAGINGDIRECTORY}"

	# Zip each Windows artifact directory into its own archive. No libiio
	# header/include bundling (not relevant to libad9166); the name matches
	# what the Cloudsmith push produces, e.g. Windows-VS-2022-x64.zip.
	for d in Windows-*/; do
		[ -d "${d}" ] || continue
		d="${d%/}"
		zip -r "${d}.zip" "${d}"
		rm -r "${d}"
	done

	# Windows installer: flatten the setup .exe to the top level so it is
	# published (action-gh-release skips nested directories).
	if [ -d Libad9166-Setup-Exe ]; then
		find Libad9166-Setup-Exe -name '*.exe' -exec mv {} ./ ";"
		rm -r Libad9166-Setup-Exe
	fi

	# Flatten every remaining per-platform artifact directory to the top level.
	# Directories are discovered at runtime instead of hard-coded, so a matrix
	# change needs no edit here. Non-release bundles are left untouched.
	for d in */; do
		d="${d%/}"
		[ -d "${d}" ] || continue
		case "${d}" in
			Artifact-manifest|libad9166-dist|libad9166-libiio-upstream-*)
				# Not part of the GitHub release; remove so the
				# `artifacts/*` upload glob cannot pick them up.
				rm -r "${d}"
				continue
				;;
			macOS-*)
				# macOS .pkg names don't carry the arch, so append it.
				pkg=$(find "${d}" -name '*.pkg' | head -1)
				if [ -z "${pkg}" ]; then
					echo "ERROR: no .pkg artifact found in ${d}" >&2
					exit 1
				fi
				base=$(basename "${pkg}")
				mv "${pkg}" "${d}/${base%.pkg}-${d}.pkg"
				;;
		esac
		find "${d}" \( -name '*.deb' -o -name '*.rpm' -o -name '*.pkg' -o -name '*.tar.gz' \) -exec mv {} ./ ";"
		rm -r "${d}"
	done
}

case "${1:-}" in
	release)
		release_artifacts
		;;
	*)
		echo "Usage: ${0} {release}" >&2
		exit 1
		;;
esac
