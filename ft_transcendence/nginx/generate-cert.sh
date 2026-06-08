#!/usr/bin/env sh
set -eu

SCRIPT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
CERT_DIR="$SCRIPT_DIR/certs"
KEY_FILE="$CERT_DIR/nginx.key"
CRT_FILE="$CERT_DIR/nginx.crt"

mkdir -p "$CERT_DIR"

if [ ! -f "$KEY_FILE" ] || [ ! -f "$CRT_FILE" ]; then
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
		-keyout "$KEY_FILE" \
		-out "$CRT_FILE" \
		-subj "/C=FR/ST=IDF/L=Paris/O=42/OU=transcendance/CN=localhost"

	chmod 600 "$KEY_FILE"
	chmod 644 "$CRT_FILE"
	echo "Certificats generes."
else
	echo "Certificats deja presents."
fi