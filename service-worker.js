// service-worker.js
self.addEventListener('install', (event) => {
  console.log('Service Worker installing...');
  event.waitUntil(
    caches.open('static-cache').then((cache) => {
      return cache.addAll([
        './',                 // Đường dẫn gốc (index.html)
        './index.html',       // Tệp HTML
        './script.js',        // Tệp JavaScript chính
        './manifest.json',    // Tệp Manifest
        './icon-192x192.png', // Biểu tượng 192px
        './icon-512x512.png'  // Biểu tượng 512px
      ]);
    })
  );
});

self.addEventListener('fetch', (event) => {
  console.log('Fetching:', event.request.url);
  event.respondWith(
    caches.match(event.request).then((response) => {
      return response || fetch(event.request);
    })
  );
});
