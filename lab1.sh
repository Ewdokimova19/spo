#!/bin/bash
echo "V kataloge" $1; find $1 ~ -type f -name ".*" | wc -l; echo "hiden files"
